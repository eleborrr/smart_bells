#include "Handlers/schedule_handlers.h"

List* handle_get_schedules(const Empty* request) {
	List* res = get_next_list(sizeof(Schedule));
	// get found schedules
	for (int i = 0; i < 5/*schedules_count*/; i++) {
		Schedule cur;
		// map found schedule with cur variable
		cur.hour = i;
		cur.minutes = i * 10;
		cur.weekdays = (1 << 6) >> i;
		sprintf(cur.filename, "%d.mid", i);
		list_add(res, &cur);
	}
	return res;
}

Empty* handle_add_schedule(const Schedule* request) {
	// save schedule in server
	return malloc(sizeof(Empty));
}

Empty* handle_edit_schedule(const EditSchedule* request) {
	// edit schedule by id(index in sent array)
	return malloc(sizeof(Empty));
}

Empty* handle_delete_schedule(const uint8_t* request) {
	// delete schedule by id
	return malloc(sizeof(Empty));
}
