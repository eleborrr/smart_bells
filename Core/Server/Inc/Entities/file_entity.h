#ifndef SERVER_INC_ENTITIES_FILE_ENTITY_H_
#define SERVER_INC_ENTITIES_FILE_ENTITY_H_

#include "list.h"
#include "serialize_utils.h"

#define DATA_LEN 16*1024

typedef struct {
	char filename[50];
	List data;
} FileInfo;

void deserialize_file_info(FileInfo* res, uint8_t** data);
void serialize_file_info(List* res, const FileInfo* ptr);
void free_file_info(FileInfo* ptr);

#endif
