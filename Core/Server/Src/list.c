#include "list.h"

#define LISTS_COUNT 150
List lists[LISTS_COUNT];
uint8_t next_list = 0;

List* get_next_list(uint32_t item_size) {
	List* res = &lists[next_list++];
	res->item_size = item_size;
	res->length = 0;
	if (next_list == LISTS_COUNT) next_list = 0;
	return res;
}

void free_list(List* list) {
	list->length = 0;
}

void list_add(List* list, const void* item) {
	list_copy_to(list, list->length, item, 1);
}

void list_list_copy_to(List* list, uint32_t index, const List* items) {
	list_copy_to(list, index, items->items, items->length);
}

void list_copy_to(List* list, uint32_t index, const void* items, uint32_t items_length) {
	uint32_t required = index + items_length;

	void* target = (void*)list_get(list, index);
	memcpy(target, items, list->item_size * items_length);
	if (required > list->length) list->length = required;
}
