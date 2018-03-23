/*
 * FlashDataBlock.cpp
 *
 *  Created on: 2 мар. 2018 г.
 *      Author: Sales
 */

#include "stm32f1xx_hal.h"
#include "crc.h"
#include <stdint.h>
#include "MC/Settings/Setting.hpp"
#include <MC/Settings/FlashDataBlock.hpp>

FlashDataBlock::FlashDataBlock():
dataChanged(false),
dataUploaded(false),
dataIntegrityFlag(false){
}

int32_t FlashDataBlock::GetInt32(uint32_t offset){
	if(!dataUploaded) UploadDataFromFlash();
	return (uint32_t)*(this->dataBuffer.data + offset);
};

bool FlashDataBlock::DataIntegrityIsOK(){
	if(!this->dataUploaded) UploadDataFromFlash();
	return this->dataIntegrityFlag;
};

void FlashDataBlock::SetInt32(int32_t newValue, uint32_t offset){
	*(this->dataBuffer.data + offset) = newValue;
	this->dataChanged = true;
};

float FlashDataBlock::GetFloat(uint32_t offset){
	if(!this->dataUploaded) this->UploadDataFromFlash();
	return (float)*(this->dataBuffer.data + offset);
}

void FlashDataBlock::SetFloat(float newValue, uint32_t offset){
	*(this->dataBuffer.data + offset) = newValue;
	this->dataChanged = true;
}

void FlashDataBlock::CommitChanges(){
	if(this->dataChanged){
		this->dataBuffer.crc = HAL_CRC_Calculate(&hcrc, (uint32_t*)this->dataBuffer.data, FLASH_DATA_SIZE32);
		uint32_t error_code = this->DownloadDataToFlash();
		if(error_code == HAL_FLASH_ERROR_NONE){
			this->dataChanged = false;
			this->dataIntegrityFlag = true;
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
	this->dataUploaded = true;
	CheckDataIntegrity();
}

void FlashDataBlock::CheckDataIntegrity(){
	uint32_t newCRC = HAL_CRC_Calculate(&hcrc, (uint32_t*)this->dataBuffer.data, FLASH_DATA_SIZE32);
	this->dataIntegrityFlag = (newCRC == this->dataBuffer.crc);
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

FlashDataBlock settingsBlock;

extern "C"{

void FlashDataBlockTest(){
	SettingFloat settingFloat1(0,0);
	SettingFloat settingFloat2(1,4);
	SettingFloat settingFloat3(2,8);
	SettingFloat settingFloat4(3,12);
	SettingFloat settingFloat5(4,16);
	SettingFloat settingFloat6(5,20);
	SettingFloat settingFloat7(6,24);
	SettingFloat settingFloat8(7,28);

	volatile float accum = 0;
	accum += settingFloat1.Get();
	accum += settingFloat2.Get();
	accum += settingFloat3.Get();
	accum += settingFloat4.Get();
	accum += settingFloat5.Get();
	accum += settingFloat6.Get();
	accum += settingFloat7.Get();
	accum += settingFloat8.Get();

	settingsBlock.CommitChanges();

	volatile uint32_t accum2 = 0;
	FlashDataBlock block2;
	for(uint32_t i = 0; i<FLASH_DATA_SIZE32; i++){
		volatile float tmp = block2.GetFloat(i);
		accum2 += tmp;
	};
}

}
