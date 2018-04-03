/*
 * FlashDataBlock.cpp
 *
 *  Created on: 2 ���. 2018 �.
 *      Author: Sales
 */

#include "stm32f1xx_hal.h"
#include "crc.h"
#include <stdint.h>
#include "MC/Settings/Setting.hpp"
#include "MC/Settings/FlashDataBlock.hpp"

static bool dataChanged;
static bool dataUploaded;
static bool dataIntegrityFlag;

static struct DataBlock {
	uint32_t crc;
	uint8_t data[FLASH_DATA_SIZE];
} dataBuffer;

FlashDataBlock::FlashDataBlock(){
	dataChanged = false;
	dataUploaded = false;
	dataIntegrityFlag = false;
	UploadDataFromFlash();
}

int32_t FlashDataBlock::GetInt32(uint32_t offset){
	if(!dataUploaded) UploadDataFromFlash();
	uint8_t* ptr8 = dataBuffer.data + offset;
	int32_t* ptr32 = (int32_t*)ptr8;
	int32_t result = *ptr32;
	return result;
};

bool FlashDataBlock::DataIntegrityIsOK(){
	if(!dataUploaded) UploadDataFromFlash();
	return dataIntegrityFlag;
};

void FlashDataBlock::SetInt32(int32_t newValue, uint16_t offset){
	uint8_t* ptr8 = dataBuffer.data + offset;
	int32_t* ptr32 = (int32_t*)ptr8;
	*ptr32 = newValue;
	dataChanged = true;
};

float FlashDataBlock::GetFloat(uint32_t offset){
	if(!dataUploaded) UploadDataFromFlash();
	uint8_t* ptr8 = dataBuffer.data + offset;
	float* ptrFloat = (float*)ptr8;
	float result = *ptrFloat;
	return result;
}

void FlashDataBlock::SetFloat(float newValue, uint16_t offset){
	uint8_t* ptr8 = dataBuffer.data + offset;
	float* ptrFloat = (float*)ptr8;
	*ptrFloat = newValue;
	dataChanged = true;
}

void FlashDataBlock::CommitChangesToFlash(){
	if(dataChanged){
		dataBuffer.crc = HAL_CRC_Calculate(&hcrc, (uint32_t*)dataBuffer.data, FLASH_DATA_SIZE32);
		uint32_t error_code = DownloadDataToFlash();
		if(error_code == HAL_FLASH_ERROR_NONE){
			dataChanged = false;
			dataIntegrityFlag = true;
		}
	};
}

void FlashDataBlock::UploadDataFromFlash(){
	uint32_t* flashAddress = (uint32_t*)FLASH_BLOCK_ADDRESS;
	uint32_t* bufferAddress = (uint32_t*)&dataBuffer;
	for(uint32_t i=0; i<FLASH_BLOCK_SIZE32; i++){
		*bufferAddress = *flashAddress;
		flashAddress++;
		bufferAddress++;
	}
	dataUploaded = true;
	CheckFlashDataIntegrity();
}

void FlashDataBlock::CheckFlashDataIntegrity(){
	uint32_t newCRC = HAL_CRC_Calculate(&hcrc, (uint32_t*)dataBuffer.data, FLASH_DATA_SIZE32);
	dataIntegrityFlag = (newCRC == dataBuffer.crc);
}

uint32_t FlashDataBlock::DownloadDataToFlash(){
	volatile uint32_t error_code;

	// Unlock flash
	error_code = HAL_FLASH_Unlock();
	if(error_code) return error_code;

	// Erase page
	FLASH_EraseInitTypeDef EraseInitStruct;
	/* Fill EraseInit structure*/
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Banks = 0;
	EraseInitStruct.PageAddress = FLASH_BLOCK_ADDRESS;
	EraseInitStruct.NbPages = 1;
	uint32_t PageError = 0;

	error_code = HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
	if(error_code) return error_code;

	// Write page

	uint64_t* flashAddress = (uint64_t*)FLASH_BLOCK_ADDRESS;
	uint64_t* bufferAddress = (uint64_t*)&dataBuffer;
	for(uint32_t i=0; i<FLASH_BLOCK_SIZE64; i++){
		uint64_t dataTmp = *bufferAddress;
		error_code = HAL_FLASH_Program(FLASH_PROC_PROGRAMDOUBLEWORD, (uint32_t)flashAddress, dataTmp);
		if(error_code) return error_code;
		flashAddress++;
		bufferAddress++;
	}
	// Lock flash
	error_code = HAL_FLASH_Lock();
	return error_code;
}
