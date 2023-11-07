#include "test_log.h"
#include "fatfs.h"
#include <string.h>
#include <stdio.h>
//some variables for FatFs
FATFS FatFs; 	//Fatfs handle
FIL fil; 		//File handle

//Read 30 bytes from "test.txt" on the SD card
BYTE readBuf[200];
FRESULT test_log_init(void)
{
	FRESULT fres = FR_OK; //Result after operations
	//Open the file system
	fres = f_mount(&FatFs, "", 1); //1=mount now
	if (fres != FR_OK)
	{
		printf("\nf_mount error (%i)\r\n", fres);
		return fres;
	}

	//Let's get some statistics from the SD card
	DWORD free_clusters, free_sectors, total_sectors;

	FATFS* getFreeFs;

	fres = f_getfree("", &free_clusters, &getFreeFs);
	if (fres != FR_OK)
	{
		printf("\nf_getfree error (%i)", fres);
		return fres;
	}

	//Formula comes from ChaN's documentation
	total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
	free_sectors = free_clusters * getFreeFs->csize;
	printf("\nSD card stats:\r\n%10lu KiB total drive space.\r\n%10lu KiB available.\r\n", total_sectors / 2, free_sectors / 2);

	return fres;
}

//FRESULT test_log_write(char* file, lcd_data_t* dat)
//{
//	FRESULT fres = FR_OK; //Result after operations
//	//Now let's try and write a file "write.txt"
//	fres = f_open(&fil, file, FA_WRITE | FA_OPEN_APPEND);
//	if(fres == FR_OK) {
//	printf("\r\nOpen %s for writing",file);
//	} else {
//		printf("\r\nf_open error (%i)", fres);
//		return fres;
//	}
//	uint8_t len;
//	//Copy in a string
//	len = sprintf((char*)readBuf, "%s,%s,%s,%d/%d/%d,%d:%d:%d,Target: %d Freq: %d Hz,Target: %d Fre: %d Hz, Target: %d Patrol: %d Fre: %d Hz/%d Hz\r\n",
//			dat->device_serial_id,dat->old_radar_id,dat->old_user_id,dat->date.Month,
//			dat->date.Date,dat->date.Year,dat->time.Hours,dat->time.Minutes,dat->time.Seconds,
//			dat->tar_1.target,dat->tar_1.fre,dat->tar_2.target,dat->tar_2.fre,dat->target,dat->patrol,dat->fre1,dat->fre2);
//	UINT bytesWrote;
//	fres = f_write(&fil, readBuf, len, &bytesWrote);
//	if(fres == FR_OK)
//	{
//		printf("\r\nWrote %i bytes to %s!", bytesWrote, file);
//	} else
//	{
//		printf("\r\nf_write error (%i)", fres);
//	}
//
//	//Be a tidy kiwi - don't forget to close your file!
//	f_close(&fil);
//	return fres;
//}
