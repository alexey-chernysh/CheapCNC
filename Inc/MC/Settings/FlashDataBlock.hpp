/*
 * FlashDataBlock.h
 *
 *  Created on: 2 ���. 2018 �.
 *      Author: Sales
 */

#ifndef FLASHDATABLOCK_HPP_
#define FLASHDATABLOCK_HPP_

#include <stdint.h>

#define FLASH_BLOCK_ADDRESS 0x0800FC00

#define FLASH_BLOCK_SIZE 64
#define FLASH_BLOCK_SIZE32 (FLASH_BLOCK_SIZE/4)
#define FLASH_BLOCK_SIZE64 (FLASH_BLOCK_SIZE/8)
#define FLASH_DATA_SIZE (FLASH_BLOCK_SIZE-4)
#define FLASH_DATA_SIZE32 (FLASH_DATA_SIZE/4)
#define FLASH_DATA_SIZE64 (FLASH_DATA_SIZE/8)

class FlashDataBlock {
public:
	FlashDataBlock();
	bool DataIntegrityIsOK();
	int32_t GetInt32(uint32_t offset);
	void SetInt32(int32_t newValue, uint16_t offset);
	float GetFloat(uint32_t offset);
	void SetFloat(float newValue, uint16_t offset);
	void CommitChangesToFlash();
private:
	void UploadDataFromFlash();
	void CheckFlashDataIntegrity();
	uint32_t DownloadDataToFlash();
};

#endif /* FLASHDATABLOCK_HPP_ */
