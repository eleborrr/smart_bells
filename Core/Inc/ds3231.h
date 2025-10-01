#include "stm32f4xx_hal.h"

#define DS3231_ADDRESS 0xD0

typedef struct {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hour;
	uint8_t dayofweek;
	uint8_t dayofmonth;
	uint8_t month;
	uint8_t year;
} TIME;


void  DS3231_Set_Time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year);
void  DS3231_Get_Time (void);
float DS3231_Get_Temp (void);
void  force_temp_conv (void);
uint8_t should_send_time();

uint8_t decToBcd(int val);
int bcdToDec(uint8_t val);
