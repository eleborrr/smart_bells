#include "packet_handler.h"

#define PACKETS_COUNT 30
Packet available_packets[PACKETS_COUNT];
uint8_t cur_packet = 0;

Packet* get_next_packet() {
	Packet* res = &available_packets[cur_packet++];
	if (cur_packet == PACKETS_COUNT) cur_packet = 0;
	res->payload = get_next_list(sizeof(uint8_t));
	return res;
}

void parse_packets(Buffer* bytes, Buffer* packets) {
	while (bytes->length >= 5) {
		BufferEnumerator e;
		start_enumerator(&e, bytes);
		buffer_enumerator_move_next(&e);
		ServerEndpoint request = *(ServerEndpoint*)buffer_enumerator_current(&e);
		List* len_temp_list = get_next_list(sizeof(uint8_t));
		for (uint8_t i = 0; i < 4 && buffer_enumerator_move_next(&e); i++) list_add(len_temp_list, buffer_enumerator_current(&e));
		uint32_t length;
		uint8_t* t = len_temp_list->items;
		deserialize_uint32(&length, (uint8_t**)&t);
		free_list(len_temp_list);

		if (bytes->length - 5 < length) {
			break;
		}

		Packet* packet = get_next_packet();
		packet->request = request;
		packet->payload = get_next_list(sizeof(uint8_t));
		while (buffer_enumerator_move_next(&e)) {
			list_add(packet->payload, buffer_enumerator_current(&e));
			if (--length == 0) break;
		}
		buffer_append(packets, packet);

		buffer_drop_first(bytes, 5 + packet->payload->length);
	}
}

List* get_packet_bytes(Packet* packet) {
	uint32_t index = 0;
	List* res = get_next_list(sizeof(uint8_t));

	index += serialize_concat_helper(res, index, &packet->request, (Serializer)serialize_uint8);
	index += serialize_concat_helper(res, index, &packet->payload->length, (Serializer)serialize_uint32);
	list_list_copy_to(res, index, packet->payload);

	return res;
}
