/*
 * uart_cmd.c
 *
 *  Created on: Oct 9, 2023
 *      Author: Loc
 */


#include "uart_cmd.h"
#include "usart.h"
#include "event.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#define UART_BUFF_SIZE   100
uint8_t uart_buf[UART_BUFF_SIZE];
char data_raw_buf[50];
uint8_t raw_count = 0;
event_id uart_cmd_id;
#define UART                   huart1
char* cmd_list[] = {"-px", "-py", "-c", "-str"}; //Example -px 10  -py 20 -c 20 -str abce

typedef struct
{
	uint16_t pixel_x;
	uint16_t pixel_y;
	uint8_t  char_size; //in pixel
	uint8_t color; // white or red;
	uint8_t chr[50]; //string
}uart_cmd_t;



typedef void (* uart_cmd_cb_t)(uart_cmd_t* cmd);



bool uart_cli_get_data(const char * buff, const char* cmd, char** data_out, uint8_t* data_len)
{
	char* result = strstr((char *)buff,(char *)cmd);
	if(result)
	{
		result += strlen(cmd); // Move to space chacracter in command
		//Remove space character
		while((*result) == ' ')
		{
			result += 1;
		}
		*data_out = result; //save pointer to out data
		//Get data until met space character or NULL
		while(((*result) != ' ') && (*result != 0))
		{
			result ++;  //Move result pointer to next buffer pos
			(* data_len)++;
		}

		return 1;
	}
	return 0;
}


void uart_data_process(char* raw, uint8_t length)
{
	if(length < 4) return; //Invalue length because \r or \n

	for(uint8_t i = 0; i < sizeof(cmd_list)/4; i ++)
	{
		uint8_t out_length = 0;
		char* data_out  = NULL;
		if(uart_cli_get_data(raw, cmd_list[i], &data_out, &out_length))
		{
			printf("\r\n");
			HAL_UART_Transmit(&UART, (uint8_t *)data_out, out_length, 10);
		}
	}
}

void uart_cmd_cb_default(uart_cmd_t* cmd)
{

}
uart_cmd_cb_t uart_cmd_cb = uart_cmd_cb_default;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == UART.Instance)
	{
	  HAL_UART_Receive_IT(&UART, uart_buf, UART_BUFF_SIZE);
	}
}

void uart_cmd_task(void)
{
	//Scan buffer
	static uint16_t chr_count = 0;
	if(uart_buf[chr_count] != 0) //filter null character
	{
		data_raw_buf[raw_count] = uart_buf[chr_count]; //Get data save raw buff
		if(uart_buf[chr_count] == 0x0A || uart_buf[chr_count] == 0x0D) //Meet enter -> receive done
		{
			uart_data_process(data_raw_buf, raw_count);   //Process data
			memset(data_raw_buf, 0, sizeof(data_raw_buf)); //Reset data_raw_buf
			raw_count = 0;  //Reset count
		}else
		{
			raw_count ++;
		}
		uart_buf[chr_count] = 0; //Reset data
		chr_count ++;
		if(chr_count >= UART_BUFF_SIZE) chr_count = 0;
	}

}

void uart_cmd_init(void* cmd_cb)
{
	if(cmd_cb != NULL) uart_cmd_cb = cmd_cb;
	HAL_UART_Receive_IT(&UART, uart_buf, UART_BUFF_SIZE);
	event_add(uart_cmd_task,&uart_cmd_id,1);
	event_active(&uart_cmd_id);
}
