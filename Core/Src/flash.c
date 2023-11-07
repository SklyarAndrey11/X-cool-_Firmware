/*
 * flash.c
 *
 */


#include "flash.h"
#include "crc.h"
#include "stm32l4xx_hal_flash.h"
#include <string.h>
#include <stdlib.h>
#include "flash_if.h"
/* Private typedef -----------------------------------------------------------*/
CRC_HandleTypeDef   CrcHandle;


enum
{
	USER_FLASH_ERROR_NONE = 0,
	USER_FLASH_WRITE_ERROR,
	USER_FLASH_ERASE_ERROR,
	USER_FLASH_EXIST_ERROR,
	USER_FLASH_INVALID_PARAM_ERROR,
	USER_FLASH_ALLOC_MEM_ERROR,
	USER_FLASH_FULL_ERROR,
	USER_FLASH_READ_ERROR,
	USE_FLASH_ERROR_OTHER,
};
/* Private define ------------------------------------------------------------*/



flash_managerment_t* f = NULL;



/**
  * @brief  Flash managerment init: read flash
  * @param  Addr: Address of the FLASH Memory
  * @retval The bank of a given address
  */
uint8_t flash_mgt_init(void)
{
	if(f == NULL)
	{
		f = calloc(1, sizeof(flash_managerment_t));
		memset((uint8_t *)f,0,sizeof(flash_managerment_t));
	}
	if(f == NULL) return USER_FLASH_ALLOC_MEM_ERROR; //Memory error

	FLASH_If_Init();
	if(*(__IO uint64_t *)FLASH_USER_START_ADDR == 0xFFFFFFFFFFFFFFFF)//First time need to
	{

		return USER_FLASH_ERASE_ERROR;
	}

  /* The 16-bit long CRC of the 9-byte buffer is computed. After peripheral initialization,
	 the CRC calculator is initialized with the user-defined value that is 0x5ABE.

	The computed CRC is stored in uint32_t uwCRCValue. The 16-bit long CRC is made of
	uwCRCValue 16 LSB bits. */

   f->crc16 = HAL_CRC_Accumulate(&CrcHandle, (uint32_t *)f, sizeof(flash_managerment_t) - 2);


	return USER_FLASH_ERROR_NONE;
}

/**
 * @brief Check data write correctly
 * @pram data: pointer to data
 * @param len: length of data
 * @param address address flash storage data
 * @return 0: Data input is the same with data from flash
 *         1: Different between data and flash
 * */
uint8_t flash_write_verify(uint32_t address, uint32_t* data, uint32_t len)
{
	if(data == NULL || address < 0x08000000) return USER_FLASH_INVALID_PARAM_ERROR;
	/* Unlock the Flash to enable the flash control register access *************/
	HAL_FLASH_Unlock();
	uint32_t* ptr = data;
	uint32_t data_r;
	while(ptr < (ptr + len/sizeof(uint32_t)))
	{
		data_r = *(__IO uint32_t *)address;
		if(data_r != *(ptr))
			return 1;
		address += sizeof(uint32_t); //Move to next address flash
		ptr += sizeof(uint32_t);     //Move to next address ram
	 }
	/* Lock the Flash to disable the flash control register access (recommended
	 to protect the FLASH memory against possible unwanted operation) */
	HAL_FLASH_Lock();
	return 0;
}

/**
 * @brief Store data ram to flash
 * @return 0: Write data with no error
 * 		   1: Error in write progress
 * */

uint8_t flash_mgt_update(void)
{
	//Erase page
	if(FLASH_If_Erase_Pages(FLASH_USER_START_ADDR, USER_FLASH_SIZE))
		return USER_FLASH_ERASE_ERROR;
	//write current flash
	if(FLASH_If_Write_Bytes(FLASH_USER_START_ADDR, (uint32_t *)f, sizeof(flash_managerment_t)) != FLASHIF_OK)
		return USER_FLASH_WRITE_ERROR;
//	if(flash_write_verify(FLASH_USER_START_ADDR, (uint32_t *)f, sizeof(flash_managerment_t)))
//		return USER_FLASH_WRITE_ERROR;
	return USER_FLASH_ERROR_NONE;
}


/**
 * @brief Create new user and save to flash
 * @param username: user name
 * @param password: password
 * @return 0: create success
 *         1: Error: flash full or invalid param
 * */
uint8_t flash_mgt_create_user(const char* username,const char* password)
{
	if(username == NULL || password == NULL) return 1;
	if((strlen(username) > USERNAME_MAX_LEN) || (strlen(password) > PASSWORD_MAX_LEN))
	{
		return USER_FLASH_EXIST_ERROR;
	}

	for(uint32_t u = 0; u < f->user_count; u++)
	{
		if(strstr(username,f->acc[u].username) == 0) return USER_FLASH_INVALID_PARAM_ERROR;// user exist
	}


	if(f->user_count >= MAX_ACCOUNT) return USER_FLASH_FULL_ERROR; //Reach max user

	strncpy(f->acc[f->user_count].username, username, strlen(username));
	strncpy(f->acc[f->user_count].password, password, strlen(password));
	f->user_count++;
	//Calculate crc16 befor update to flash
	f->crc16 = HAL_CRC_Accumulate(&CrcHandle, (uint32_t *)f, sizeof(flash_managerment_t) - 2);
	uint8_t status = flash_mgt_update();
	return status;
}

uint8_t flash_mgt_save_device_id(const char* devId)
{
	if(devId == NULL) return 1;
	strncpy(f->devId,devId,strlen(devId));
	//Calculate crc16 befor update to flash
	f->crc16 = HAL_CRC_Accumulate(&CrcHandle, (uint32_t *)f, sizeof(flash_managerment_t) - 2);
	uint8_t status = flash_mgt_update();
	return status;
}

/**
 * @brief Read data from flash
 * @return 0: No error
 *         x: Error readew
 * */
uint8_t flash_mgt_read(void)
{
	uint64_t* ptr = (uint64_t *)f;
	uint32_t len = sizeof(flash_managerment_t);
	uint32_t address = FLASH_USER_START_ADDR;
	while(ptr < (ptr + len/sizeof(uint64_t)))
	{
		*(ptr) = *(__IO uint64_t *)address;
		address += sizeof(uint64_t); //Move to next address flash
		ptr ++;     //Move to next address ram
	 }
	uint16_t crc16 = HAL_CRC_Accumulate(&CrcHandle, (uint32_t *)f, sizeof(flash_managerment_t) - 2);
	if(crc16 != f->crc16) return USER_FLASH_READ_ERROR;
	return USER_FLASH_ERROR_NONE;
}




