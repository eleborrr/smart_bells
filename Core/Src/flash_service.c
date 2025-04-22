//#include <flash_service.h>
//
///**
// * @brief функция считывает значения структуры "test_struct", записанные ранее во flash
// * @param addr - адрес в памяти микроконтроллера
// */
//void readFlash (uint32_t addr)
//{
//	uint32_t structureSize = sizeof(test_struct);
//	uint32_t *dataPtr = (uint32_t *)&test_struct;
//	for (int i = 0; i < structureSize / 4; i++)
//	{
//		dataPtr[i] = *(__IO uint32_t*)addr;
//		addr += 4;
//	}
//}
//
///**
// * @brief Функция записывает структуру "test_struct" во flash память микроконтроллера
// * @param addr - адрес в памяти микроконтроллера
// * @return статус операции
// */
//uint8_t writeFlash (uint32_t addr)
//{
////	HAL_StatusTypeDef status;
//	uint32_t structureSize = sizeof(test_struct);          // замеряем размер структуры
////	FLASH_EraseInitTypeDef FlashErase;                     // структура для функции стирания страницы
////	uint32_t sectorError = 0;                              // переменная для записи информации об ошибках в процессе стирания
//
//	uint32_t *dataPtr = (uint32_t *)&test_struct;          // создаем указатель на нашу структуру и записываем ее кусочками по 32 бита
//
//
//	FLASH_Erase_Sector(FLASH_SECTOR_5, FLASH_VOLTAGE_RANGE_1);
//	HAL_FLASH_Unlock();                                    // разлочить память
//
//	for (uint8_t i = 0; i < structureSize / 4; i++)
//	{
//		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, dataPtr[i]) != HAL_OK)
//				return 1;
//		addr += 4;
//	}
//
//	HAL_FLASH_Lock();
//
//	return 0;
//
//
////	FlashErase.TypeErase = FLASH_TYPEERASE_SECTORS;
////	FlashErase.NbSectors = 1;
////	FlashErase.Sector = FLASH_SECTOR_5;
////	FlashErase.VoltageRange = VOLTAGE_RANGE_3;
////	if (HAL_FLASHEx_Erase(&FlashErase, &sectorError) != HAL_OK)   // вызов функции стирания
////	{
////		HAL_FLASH_Lock();                                  // если не смог стереть, то закрыть память и вернуть ошибку
////        __enable_irq();
////		return HAL_ERROR;
////	}
////	uint32_t *dataPtr = (uint32_t *)&test_struct;          // создаем указатель на нашу структуру и записываем ее кусочками по 32 бита
////	for (uint8_t i = 0; i < structureSize / 4; i++)
////	{
////		status += HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, dataPtr[i]);
////		addr += 4;
////	}
////	__enable_irq();                                        // включаем прерывания обратно
////	return status;
//}
