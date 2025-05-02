//#include <settings_manager.h>
//#include "stm32f4xx_hal_flash.h"
//
//void LoadSettings(Settings *settings) {
//    const Settings *flash_settings = (Settings*)SETTINGS_FLASH_ADDR;
//
//    // Проверяем magic number и checksum
//    if (flash_settings->magic == 0xDEADBEEF &&
//        CalculateChecksum(flash_settings) == flash_settings->checksum) {
//        memcpy(settings, flash_settings, sizeof(Settings));
//    } else {
//        // Загрузка настроек по умолчанию
//        memset(settings, 0, sizeof(Settings));
//        settings->magic = 0xDEADBEEF;
//    }
//}
//
//void SaveSettings(Settings *settings) {
//    FLASH_EraseInitTypeDef erase;
//    uint32_t sector_error;
//
//    // Рассчитываем контрольную сумму
//    settings->checksum = CalculateChecksum(settings);
//
//    // Разблокируем Flash
//    HAL_FLASH_Unlock();
//
//    // Стираем страницу (для F4 сектор 11)
//    erase.TypeErase = FLASH_TYPEERASE_SECTORS;
//    erase.Sector = FLASH_SECTOR_11;
//    erase.NbSectors = 1;
//    erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
//
//    HAL_FLASHEx_Erase(&erase, &sector_error);
//
//    // Пишем данные (по 64 бита)
//    uint64_t *data = (uint64_t*)settings;
//    for (int i = 0; i < sizeof(Settings); i += 8) {
//        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,
//                         SETTINGS_FLASH_ADDR + i,
//                         data[i/8]);
//    }
//
//    HAL_FLASH_Lock();
//}
