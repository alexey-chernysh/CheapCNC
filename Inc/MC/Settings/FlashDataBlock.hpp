/*
 * FlashDataBlock.h
 *
 *  Created on: 2 мар. 2018 г.
 *      Author: Sales
 */

#ifndef FLASHDATABLOCK_HPP_
#define FLASHDATABLOCK_HPP_

#include <stdint.h>

#define FLASH_BLOCK_ADDRESS 0x0800FC00

#define FLASH_BLOCK_SIZE 1024
#define FLASH_BLOCK_SIZE32 (FLASH_BLOCK_SIZE/4)
#define FLASH_BLOCK_SIZE64 (FLASH_BLOCK_SIZE/8)
#define FLASH_DATA_SIZE (FLASH_BLOCK_SIZE-4)
#define FLASH_DATA_SIZE32 FLASH_DATA_SIZE/4

class FlashDataBlock {
private:
	bool dataChanged;
	bool dataUploaded;
	bool dataIntegrityFlag;
	struct DataBlock {
		uint32_t crc;
		uint8_t data[FLASH_DATA_SIZE];
	} dataBuffer;

public:
	FlashDataBlock();
	bool DataIntegrityIsOK();
	int32_t GetInt32(uint32_t offset);
	void SetInt32(int32_t newValue, uint32_t offset);
	float GetFloat(uint32_t offset);
	void SetFloat(float newValue, uint32_t offset);
	void CommitChanges();
private:
	void UploadDataFromFlash();
	void CheckDataIntegrity();
	uint32_t DownloadDataToFlash();
};

extern FlashDataBlock settingsBlock;

#endif /* FLASHDATABLOCK_HPP_ */
