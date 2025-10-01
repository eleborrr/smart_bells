#ifndef SERVER_INC_HANDLERS_BELL_SETTINGS_HANDLERS_H_
#define SERVER_INC_HANDLERS_BELL_SETTINGS_HANDLERS_H_

#include "Entities/bell_settings.h"
#include "Entities/two_bells.h"
#include "Entities/empty.h"

List* handle_get_bell_settings(const Empty* request);
Empty* handle_try_single_bell(const BellSettings* request);
Empty* handle_compare_two_bells(const TwoBells* request);
Empty* handle_save_bell_settings(const List* request);

#endif
