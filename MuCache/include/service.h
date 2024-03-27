#ifndef SERVICE_H
#define SERVICE_H

#include <map>
#include "request.h"
#include "wrapper.h"
#include "cachemanager.h"
#include <stack>
#include <mutex>

class Service
{
public:
    int id;
    std::map<int, std::pair<bool, int>> cache; // key to (valid, value)
    std::map<int, int> content;                // key to value
    Wrapper *wrapper;
    CacheManager *cachemanager;

    Service(int id_, Wrapper *wrapper_, CacheManager *cachemanager_);
    void handleRequest(Request req);
};

#endif