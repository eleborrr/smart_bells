#include "server_endpoints.h"

List endpoints;

void register_endpoint(ServerEndpoint endpoint,
		Deserializer deserialize_request, Serializer serialize_response,
		FreeFunc free_request, FreeFunc free_response,
		Handler handler) {
	if (!endpoints.item_size) endpoints.item_size = sizeof(EndpointMeta);

	EndpointMeta* endpoint_meta = malloc(sizeof(EndpointMeta));
	endpoint_meta->endpoint = endpoint;
	endpoint_meta->deserialize_request = deserialize_request;
	endpoint_meta->serialize_response = serialize_response;
	endpoint_meta->free_request = free_request;
	endpoint_meta->free_response = free_response;
	endpoint_meta->handler = handler;

	list_add(&endpoints, endpoint_meta);
}

const EndpointMeta* get_endpoint_meta(ServerEndpoint endpoint) {
	EndpointMeta* cur;
	list_foreach((&endpoints), cur)
		if (cur->endpoint == endpoint)
			return cur;

	return NULL;
}
