#include "Handlers/sync_time_handler.h"
#include "ds3231.h"

SyncTime* handle_sync_time(const SyncTime *request) {
	//TODO set day of week
	DS3231_Set_Time(request->seconds, request->minutes, request->hours, 0, request->day, request->month, request->year - 2000);
	// save use time in server
	return (SyncTime*)request;
}
