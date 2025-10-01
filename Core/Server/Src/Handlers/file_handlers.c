#include "Handlers/file_handlers.h"
#include "midi.h"

List* handle_get_files(const Empty* request) {
	List* res = get_next_list(sizeof(char[50]));
	// get all files
	for (int i = 0; i < 5/*file_count*/; i++) {
		// get found file name
		char filename[50];
		sprintf(filename, "test_file_%d.mid", i);
		list_add(res, filename);
	}
	return res;
}

Empty* handle_add_file(const FileInfo* request) {
	// create file with name `request->filename`
	// set content from request->data->items
	return malloc(sizeof(Empty));
}

Empty* handle_edit_file(const EditFile* request) {
	// find file by request->old_name, rename to request->new_name
	return malloc(sizeof(Empty));
}

char* handle_play_file(const char* request) {
	play_midi(request);
	return (char*)request;
}

char* handle_delete_file(const char* request) {
	// delete file by name
	return (char*)request;
}

void serialize_strings_list(List* res, const List* ptr) {
	serialize_list(res, ptr, (Serializer)serialize_string);
}

