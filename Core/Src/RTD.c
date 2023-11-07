/*
 * RTD.c
 *
 */


#include "RTD.h"
#include "main.h"
#include "adc.h"
#include "event.h"
#include "stm32l4xx_hal.h"
#include "quartic.h"
#define ADC_VREF_mV           3359       //Voltage adc in mV
#define RTD_MAX_CHANNEL   6
uint32_t adc_buff[RTD_MAX_CHANNEL];
uint16_t temper[RTD_MAX_CHANNEL];
event_id rtd_id;
#define RES_OFFSET_CALIB     60
//2118  2852
//      4096
//0.00375 ±0.000029 ohm -> 1 kohm  0c
//

#define SAMPLE_MAX_COUNT    100
uint8_t rtd1_count = 0;

uint32_t rtd1_adc_total = 0;
volatile uint32_t rtd1_average = 0;
uint32_t rtd1_voltage = 0;
uint32_t rtd1_res = 0;
#define MAX_TEMPERATURE

uint32_t adc_to_mV(uint32_t input)
{
	return input * ADC_VREF_mV/4095;
}

uint32_t mV_to_ohm(uint32_t input)
{
	return input/2;
}



/*
Constant        1000 Ω              100 Ω
Alpha α (°C-1) 0.00375 ±0.000029    0.003850 ±0.000010
Delta δ (°C)   1.605 ±0.009         1.4999 ±0.007
Beta β  (°C)   0.16                 0.10863
A (°C-1)       3.81 x 10^-3         3.908 x 10-3
B (°C-2)      -6.02 x 10^-7         -5.775 x 10-7
C (°C-4)      -6.0 x 10^-12         -4.183 x 10-12

 * Functional Behavior
RT = R0(1 + AT + BT2 - 100CT3 + CT4)
Where:
RT = Resistance (Ω) at temperature T (°C)
R0 = Resistance (Ω) at 0 °C
T = Temperature (°C)
A = α + αδ    B = -αδ     CT<0 = -αβ
     100      100^2          100^4
*/



double alpha =   0.00375;
double delta =   1.605;
double beta =    0.16;
double A     =   3.81/10000;
double B     =   -6.02/10000000;
double C     =   -6/1000000000000;
double R0    =   1000; //resistance at 0 degree C


//in quartic


double a = 100;//
double b = 6.02 * 100000/6;//  B/C ;
double c = -3.81*1000000000/6;//A/C;
double d = 0;//(1 -  rtd1_res/R0)*1000000000000/6;

double temp_result = 0;
void rtd_task(void)
{
	d =  ((rtd1_res)/R0 - 1)*1000000000000/6;
	DComplex *result = solve_quartic(a,b,c,d);
	temp_result = creal(result[3]);
	event_inactive(&rtd_id);
}

double rtd_get_temperature(void)
{
	return temp_result;
}

void rtd_init(void)
{
	event_add(rtd_task, &rtd_id, 100);
	event_active(&rtd_id);

	HAL_ADC_Start_DMA(&hadc1, adc_buff, 6);
}

volatile uint32_t adc_tick = 0;;
volatile uint32_t adc_current_tick = 0;
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	adc_tick = HAL_GetTick() - adc_current_tick;
	adc_current_tick = HAL_GetTick();
	rtd1_adc_total += adc_buff[2];
	rtd1_count++;
	if(rtd1_count >= SAMPLE_MAX_COUNT)
	{
		rtd1_average = rtd1_adc_total/SAMPLE_MAX_COUNT;
		rtd1_voltage = adc_to_mV(rtd1_average);
		rtd1_res = mV_to_ohm(rtd1_voltage) + RES_OFFSET_CALIB;
		event_active(&rtd_id);

		rtd1_adc_total = 0;
		rtd1_count = 0;
	}
}



