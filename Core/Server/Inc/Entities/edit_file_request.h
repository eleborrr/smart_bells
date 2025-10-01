#ifndef SERVER_INC_ENTITIES_EDIT_FILE_REQUEST_H_
#define SERVER_INC_ENTITIES_EDIT_FILE_REQUEST_H_

#include "list.h"
#include "serialize_utils.h"

#define MAX_FILE_NAME_LENGTH 50

typedef struct {
	char old_filename[MAX_FILE_NAME_LENGTH];
	char new_filename[MAX_FILE_NAME_LENGTH];
} EditFile;

void deserialize_edit_file(EditFile* res, uint8_t** data);
void serialize_edit_file(List* res, const EditFile* ptr);
void free_edit_file(EditFile* ptr);

#endif
