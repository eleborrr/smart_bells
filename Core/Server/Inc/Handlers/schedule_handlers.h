#ifndef SERVER_INC_HANDLERS_SCHEDULE_HANDLERS_H_
#define SERVER_INC_HANDLERS_SCHEDULE_HANDLERS_H_

#include "Entities/schedule.h"
#include "Entities/edit_schedule.h"
#include "Entities/empty.h"

List* handle_get_schedules(const Empty* request);
Empty* handle_add_schedule(const Schedule* request);
Empty* handle_edit_schedule(const EditSchedule* request);
Empty* handle_delete_schedule(const uint8_t* request);

#endif
