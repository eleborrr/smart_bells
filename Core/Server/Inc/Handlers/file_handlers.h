#ifndef SERVER_INC_HANDLERS_FILE_HANDLERS_H_
#define SERVER_INC_HANDLERS_FILE_HANDLERS_H_

#include "Entities/file_entity.h"
#include "Entities/edit_file_request.h"
#include "Entities/empty.h"
#include "stdio.h"

List* handle_get_files(const Empty* request);
Empty* handle_add_file(const FileInfo* request);
Empty* handle_edit_file(const EditFile* request);
char* handle_play_file(const char* request);
char* handle_delete_file(const char* request);

void serialize_strings_list(List* res, const List* ptr);

#endif
