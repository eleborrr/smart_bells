#include "packet.h"

void free_packet(Packet* packet) {
	if (packet->payload) {
		free_list(packet->payload);
	}
}
