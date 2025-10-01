#ifndef SERVER_INC_LIST_H_
#define SERVER_INC_LIST_H_

#include "stdint.h"
#include "stdlib.h"
#include "string.h"

typedef struct {
	uint8_t items[512];
	uint32_t length;
	uint32_t item_size;
} List;

List* get_next_list(uint32_t item_size);
void free_list(List* list);
void list_add(List* list, const void* item);
void list_copy_to(List* list, uint32_t index, const void* items, uint32_t items_length);
void list_list_copy_to(List* list, uint32_t index, const List* items);

//#define _GET_MACRO(_1, _2, NAME, ...) NAME
//#define _List_of_1(T) init_list(sizeof(T), 4)
//#define _List_of_2(T, capacity) init_list(sizeof(T), capacity);
//#define List_of(...) _GET_MACRO(__VA_ARGS__, _List_of_2, _List_of_1)(__VA_ARGS__)

#define list_get(list, index) ((uint8_t*)list->items + list->item_size * index)
#define list_set(list, index, val) list_copy_to(list, index, &val, 1)
#define list_foreach(list, var) \
	for (uint32_t i = 0; i < list->length && (var = list_get(list, i), 1); i++)

#endif
