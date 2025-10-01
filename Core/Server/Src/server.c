#include "server.h"
#include "Handlers/schedule_handlers.h"

void do_not_free(const void* ptr) {}

void init_server() {
	init_esp(1);
	init_state_machine();
	start_receive(&huart3);

	REGISTER_ENDPOINT_TYPED(SEP_SERVER_TIME,
			NULL, SyncTime,
			NULL, serialize_sync_time,
			NULL, do_not_free,
			NULL);

	REGISTER_ENDPOINT_TYPED(SEP_GET_SCHEDULES,
			Empty, List,
			deserialize_empty, serialize_schedules_list,
			free_empty, free_list,
			handle_get_schedules);
	REGISTER_ENDPOINT_TYPED(SEP_ADD_SCHEDULE,
			Schedule, Empty,
			deserialize_schedule, serialize_empty,
			free_schedule, free_empty,
			handle_add_schedule);
	REGISTER_ENDPOINT_TYPED(SEP_EDIT_SCHEDULE,
			EditSchedule, Empty,
			deserialize_edit_schedule, serialize_empty,
			free_edit_schedule, free_empty,
			handle_edit_schedule);
	REGISTER_ENDPOINT_TYPED(SEP_DELETE_SCHEDULE,
			uint8_t, Empty,
			deserialize_uint8, serialize_empty,
			free, free_empty,
			handle_delete_schedule);

	REGISTER_ENDPOINT_TYPED(SEP_GET_FILES,
			Empty, List,
			deserialize_empty, serialize_strings_list,
			free_empty, free_list,
			handle_get_files);
	REGISTER_ENDPOINT_TYPED(SEP_ADD_FILE,
			FileInfo, Empty,
			deserialize_file_info, serialize_empty,
			free_file_info, free_empty,
			handle_add_file);
	REGISTER_ENDPOINT_TYPED(SEP_EDIT_FILE,
			EditFile, Empty,
			deserialize_edit_file, serialize_empty,
			free_edit_file, free_empty,
			handle_edit_file);
	REGISTER_ENDPOINT_TYPED(SEP_PLAY_FILE,
			char[50], char[50],
			deserialize_string, serialize_string,
			free, do_not_free,
			handle_play_file);
	REGISTER_ENDPOINT_TYPED(SEP_DELETE_FILE,
			char[50], char[50],
			deserialize_string, serialize_string,
			free, do_not_free,
			handle_delete_file);

	REGISTER_ENDPOINT_TYPED(SEP_SYNC_TIME,
			SyncTime, SyncTime,
			deserialize_sync_time, serialize_sync_time,
			free_sync_time, do_not_free,
			handle_sync_time);

	REGISTER_ENDPOINT_TYPED(SEP_GET_BELL_SETTINGS,
			Empty, List,
			deserialize_empty, serialize_bell_settings_list,
			free_empty, free_list,
			handle_get_bell_settings);
	REGISTER_ENDPOINT_TYPED(SEP_TRY_SINGLE_BELL,
			BellSettings, Empty,
			deserialize_bell_settings, serialize_empty,
			free_bell_settings, free_empty,
			handle_try_single_bell);
	REGISTER_ENDPOINT_TYPED(SEP_COMPARE_TWO_BELLS,
			TwoBells, Empty,
			deserialize_two_bells, serialize_empty,
			free_two_bells, free_empty,
			handle_compare_two_bells);
	REGISTER_ENDPOINT_TYPED(SEP_SAVE_BELL_SETTINGS,
			List, Empty,
			deserialize_bell_settings_list, serialize_empty,
			free_list, free_empty,
			handle_save_bell_settings);
}
