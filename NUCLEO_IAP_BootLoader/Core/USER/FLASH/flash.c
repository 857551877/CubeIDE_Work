#include "flash.h"


uint8_t Flash_Write_Page(uint32_t Flash_Address, uint32_t *Data_Address) {

	HAL_FLASH_Unlock(); //Unlock

	uint32_t PageError;
	FLASH_EraseInitTypeDef EraseInitStruct; //erase Struct init
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES; //erase a page
	EraseInitStruct.PageAddress = Flash_Address;
	EraseInitStruct.NbPages = 1; //1 page
	if(HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK) {
		return 1; //erase error occur
	}

	for(uint32_t i = 0; i < 256; i++) {
		//if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Flash_Address + i * 4, *(Data_Address + i * 4)) != HAL_OK) {
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Flash_Address + i * 4, *(Data_Address + i)) != HAL_OK) {
			return 2; //Flash program error occur
		}


	}


	HAL_FLASH_Lock(); //Lock

	return 0;

}
