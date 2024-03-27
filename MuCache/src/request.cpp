#include "request.h"

Request::Request(int id_, int caller_id_, int dest_id_, int dest_key_, bool isRO_, int value_) : id(id_), caller_id(caller_id_), dest_id(dest_id_), dest_key(dest_key_), isRO(isRO_), value(value_) {}