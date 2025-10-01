#ifndef INC_PACKET_HANDLER_H_
#define INC_PACKET_HANDLER_H_

#include "stdint.h"
#include "buffer.h"
#include "packet.h"
#include "list.h"

void parse_packets(Buffer* bytes, Buffer* packets);
List* get_packet_bytes(Packet* packet);

#endif
