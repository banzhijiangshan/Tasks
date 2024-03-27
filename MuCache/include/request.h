#ifndef REQUEST_H
#define REQUEST_H

#include <cstring>

class Request
{
public:
    bool isRO;
    int id;
    int caller_id;
    int dest_id;
    int dest_key;
    int value;

    Request(int id_, int caller_id_, int dest_id_, int dest_key_, bool isRO_ = true, int value_ = 0);
};

#endif