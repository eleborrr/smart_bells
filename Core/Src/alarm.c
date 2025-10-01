#include <stdlib.h>
#include <stdint.h>
#include "alarm.h"
#include "ds3231.h"

Alarm alarmSchedule[MAX_ALARMS];
uint16_t currentAlarmCount = 0;
uint32_t lastAlarmCheck = 0;
uint8_t alarmTriggered = 0;
Alarm triggeredAlarm;

extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim2;
extern TIME time;

void saveAlarmsToSD() {
   FRESULT res;
   UINT bytesWritten;

   res = f_mount(&fs, "", 1);
   if(res != FR_OK) return;

   res = f_open(&alarmFile, "alarms.dat", FA_WRITE | FA_CREATE_ALWAYS);
   if(res != FR_OK) {
       f_mount(NULL, "", 0);
       return;
   }

   for(int i = 0; i < currentAlarmCount; i++) {
       f_write(&alarmFile, &alarmSchedule[i], sizeof(Alarm), &bytesWritten);
   }

   f_close(&alarmFile);
   f_mount(NULL, "", 0);
}

void initAlarm(){
	for(int i = 0; i < 10; i++){
		Alarm alarm;
		alarm.dayOfWeek = 1;
		alarm.hour = 0;
		alarm.isActive = 1;
		alarm.minute = i;
		alarmSchedule[i] = alarm;
	}
	currentAlarmCount = 10;
}

void saveAlarm(uint8_t day, uint8_t hour, uint8_t minute) {
    if(currentAlarmCount < MAX_ALARMS) {
        alarmSchedule[currentAlarmCount].dayOfWeek = day;
        alarmSchedule[currentAlarmCount].hour = hour;
        alarmSchedule[currentAlarmCount].minute = minute;
        alarmSchedule[currentAlarmCount].isActive = 1;
        currentAlarmCount++;
       saveAlarmsToSD();
    }
}

void checkAlarmsNonBlocking() {
    static uint32_t lastCheckTick = 0;
    uint32_t currentTick = HAL_GetTick();
    char output[100];

    if((currentTick - lastCheckTick) >= ALARM_CHECK_INTERVAL) {
		lastCheckTick = currentTick;

		for(int i = 0; i < currentAlarmCount; i++) {
			if(alarmSchedule[i].isActive &&
			   alarmSchedule[i].dayOfWeek == time.dayofweek &&
			   alarmSchedule[i].hour == time.hour &&
			   alarmSchedule[i].minute == time.minutes){
				   alarmTriggered = 1;
				   break;
			}
		}
	}
}

void processAlarm() {
    if(alarmTriggered) {
   	play_midi(triggeredAlarm->filename);
        alarmTriggered = 0;
    }
}
