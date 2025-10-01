#ifndef INC_SERVER_ENDPOINTS_H_
#define INC_SERVER_ENDPOINTS_H_

#include "stdint.h"
#include "stdlib.h"
#include "serialize_utils.h"

typedef enum ServerEndpoint {
	SEP_SERVER_TIME = 0,
	SEP_GET_SCHEDULES = 1,
	SEP_ADD_SCHEDULE = 2,
	SEP_EDIT_SCHEDULE = 3,
	SEP_DELETE_SCHEDULE = 4,
	SEP_GET_FILES = 5,
	SEP_ADD_FILE = 6,
	SEP_EDIT_FILE = 7,
	SEP_PLAY_FILE = 8,
	SEP_DELETE_FILE = 9,
	SEP_SYNC_TIME = 10,
	SEP_GET_BELL_SETTINGS = 11,
	SEP_TRY_SINGLE_BELL = 12,
	SEP_COMPARE_TWO_BELLS = 13,
	SEP_SAVE_BELL_SETTINGS = 14,
} ServerEndpoint;

typedef void* (*Handler) (const void* request);

typedef struct EndpointMeta {
	ServerEndpoint endpoint;

	Deserializer deserialize_request;
	Serializer serialize_response;

	FreeFunc free_request;
	FreeFunc free_response;

	Handler handler;
} EndpointMeta;

#define REGISTER_ENDPOINT_TYPED(endpoint, RequestType, ResponseType, \
		deserialize_request, serialize_response, free_request, free_response, handler) \
		register_endpoint(endpoint, \
				(Deserializer) deserialize_request, (Serializer) serialize_response, \
				(FreeFunc) free_request, (FreeFunc) free_response, \
				(Handler) handler)

void register_endpoint(ServerEndpoint endpoint,
		Deserializer deserialize_request, Serializer serialize_response,
		FreeFunc free_request, FreeFunc free_response,
		Handler handler);
const EndpointMeta* get_endpoint_meta(ServerEndpoint endpoint);

#endif
