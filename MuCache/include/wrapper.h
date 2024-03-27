#ifndef WRAPPER_H
#define WRAPPER_H

#include <map>
#include <set>
#include <unistd.h>
#include <iostream>

extern std::map<int, std::set<int>> readset; // request_id to keys

class Wrapper
{
public:
    int service_id;
    class context
    {
    public:
        int request_id;
        int caller_id;
        int dest_id;
        int dest_key;
        bool isRO;
        std::set<int> visited;

        context() {}
        context(int request_id_, int caller_id_, int dest_id_, int dest_key_, bool isRO_ = true) : request_id(request_id_), caller_id(caller_id_), isRO(isRO_), dest_id(dest_id_), dest_key(dest_key_) {}
    } ctx;

    Wrapper(int service_id_);
    void preStart();
    void preRead(int k);
    void Read();
    void preReturn();
    void postWrite(int k, int v);
    bool preCall();
    void save(int k, int v);
};

#endif