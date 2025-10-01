#define MAX_ALARMS 100
#define ALARM_CHECK_INTERVAL 60000 // ms
#define ALARM_FILENAME_LEN 32

#include "stm32f4xx_hal.h"

typedef struct {
    uint8_t dayOfWeek;
    uint8_t hour;
    uint8_t minute;
    uint8_t isActive;
    char filename[ALARM_FILENAME_LEN];
} Alarm;

void saveAlarm(uint8_t day, uint8_t hour, uint8_t minute);
