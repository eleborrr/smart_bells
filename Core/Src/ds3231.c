#include "ds3231.h"
#include "state_machine.h"
#include "Entities/sync_time.h"
TIME time;
extern I2C_HandleTypeDef hi2c1;
uint8_t get_time[7];

/**
 * @brief Decodes the raw binary value stored in registers to decimal format.
 * @param bin Binary-coded decimal value retrieved from register, 0 to 255.
 * @return Decoded decimal value.
 */

TIME prev_sent_time = {0,};

uint8_t should_send_time() {
  uint8_t res = (time.seconds != prev_sent_time.seconds ||
      time.minutes != prev_sent_time.minutes ||
      time.hour != prev_sent_time.hour ||
      time.dayofmonth != prev_sent_time.dayofmonth ||
      time.month != prev_sent_time.month ||
      time.year != prev_sent_time.year);
  if (res){
	  prev_sent_time = time;
  }
  return res;
}




uint8_t decToBcd(int val)
{
  return (uint8_t)( (val/10*16) + (val%10) );
}

int bcdToDec(uint8_t val)
{
  return (int)( (val/16*10) + (val%16) );
}

void DS3231_Set_Time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year)
{
	uint8_t set_time[7];
	set_time[0] = decToBcd(sec);
	set_time[1] = decToBcd(min);
	set_time[2] = decToBcd(hour);
	set_time[3] = decToBcd(dow);
	set_time[4] = decToBcd(dom);
	set_time[5] = decToBcd(month);
	set_time[6] = decToBcd(year % 100);

	uint8_t ret;

	ret = HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, 0x00, 1, set_time, 7, 1000);
}

void DS3231_Get_Time (void)
{
//	HAL_I2C_Master_Receive_IT(&hi2c1, DS3231_ADDRESS, get_time, 7);
	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x00, 1, get_time, 7, 1000);

	time.seconds = bcdToDec(get_time[0]);
	time.minutes = bcdToDec(get_time[1]);
	time.hour = bcdToDec(get_time[2]);
//	stm_mstime.seconds = bcdToDec(get_time[0]);
//	stm_ms.time.minutes = bcdToDec(get_time[1]);
//	stm_ms.time.hour 	= bcdToDec(get_time[2]);

//	time.dayofweek = bcdToDec(get_time[3]);
	time.dayofmonth = bcdToDec(get_time[4]);
	time.month = bcdToDec(get_time[5]);
	time.year = bcdToDec(get_time[6]);
}


float DS3231_Get_Temp (void)
{
	uint8_t temp[2];

	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x11, 1, temp, 2, 1000);
	return ((temp[0])+(temp[1]>>6)/4.0);
}

void force_temp_conv (void)
{
	uint8_t status=0;
	uint8_t control=0;
	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x0F, 1, &status, 1, 100);  // read status register
	if (!(status&0x04))
	{
		HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x0E, 1, &control, 1, 100);  // read control register
		HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, 0x0E, 1, (uint8_t *)(control|(0x20)), 1, 100);
	}
}
