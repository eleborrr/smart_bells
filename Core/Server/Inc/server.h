#ifndef INC_SERVER_H_
#define INC_SERVER_H_

#include "state_machine.h"
#include "esp.h"
#include "server_endpoints.h"

#include "Handlers/bell_settings_handlers.h"
#include "Handlers/file_handlers.h"
#include "Handlers/schedule_handlers.h"
#include "Handlers/sync_time_handler.h"

void init_server();

#endif
