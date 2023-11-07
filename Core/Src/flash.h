/*
 * flash.h
 *
 */

#ifndef SRC_FLASH_H_
#define SRC_FLASH_H_
#include <stdint.h>
#include "flash_if.h"
#include "flash_page.h"
#define FLASH_USER_START_ADDR   ADDR_FLASH_PAGE_50   /* Start @ of user Flash area */
#define USER_FLASH_SIZE         0x800               /*1 page*/

#define DEVICE_ID_MAX_LEN    7
#define USERNAME_MAX_LEN     7
#define PASSWORD_MAX_LEN     7
#define SIZE_OF_FLASH_MANAGEMENT (4 + USERNAME_MAX_LEN + PASSWORD_MAX_LEN + PASSWORD_MAX_LEN + 4)
#define MAX_ACCOUNT          (USER_FLASH_SIZE/SIZE_OF_FLASH_MANAGEMENT)



typedef struct
{
	char username[USERNAME_MAX_LEN];
	char password[PASSWORD_MAX_LEN];
}account_info_t;
typedef struct
{
	union
	{
		struct
		{
			uint32_t user_count;
			char devId[DEVICE_ID_MAX_LEN];
			account_info_t acc[MAX_ACCOUNT];
			uint16_t crc16;
		};
		uint64_t profile[256];
	};
}flash_managerment_t;



extern flash_managerment_t* f;


uint8_t flash_mgt_init(void);
uint8_t flash_mgt_create_user(const char* username,const char* password);
uint8_t flash_mgt_save_device_id(const char* devId);
uint8_t flash_mgt_read(void);
#endif /* SRC_FLASH_H_ */
