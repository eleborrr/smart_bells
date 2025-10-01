#ifndef INC_PACKET_H_
#define INC_PACKET_H_

#include "server_endpoints.h"
#include "stdint.h"
#include "list.h"

typedef struct {
	ServerEndpoint request;
	List *payload;
} Packet;

void free_packet(Packet* packet);

#endif
