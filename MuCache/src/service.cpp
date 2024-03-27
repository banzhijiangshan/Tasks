#include "service.h"
#include "wrapper.h"

extern int path[10][10];
extern std::map<int, Wrapper *> allWrappers;
std::mutex mtx;

Service::Service(int id_, Wrapper *wrapper_, CacheManager *cachemanager_) : id(id_), wrapper(wrapper_), cachemanager(cachemanager_)
{
    cache.clear();
    content.clear();
}

void Service::handleRequest(Request req)
{
    mtx.lock();
    wrapper->ctx.isRO = req.isRO;
    wrapper->ctx.request_id = req.id;
    wrapper->ctx.dest_id = req.dest_id;
    wrapper->ctx.dest_key = req.dest_key;
    wrapper->ctx.caller_id = req.caller_id;

    if (!req.isRO)
    {
        wrapper->postWrite(req.dest_key, req.value);
        mtx.unlock();
        return;
    }
    wrapper->preStart();

    std::stack<int> route;
    route.push(req.dest_id);
    int cur = req.dest_id;
    while (cur != id)
    {
        route.push(path[id][cur]);
        cur = path[id][cur];
    }
    mtx.unlock();
    while (!route.empty())
    {
        int next = route.top();
        route.pop();
        if (next == id)
        {
            mtx.lock();
            wrapper->ctx.isRO = req.isRO;
            wrapper->ctx.request_id = req.id;
            wrapper->ctx.dest_id = req.dest_id;
            wrapper->ctx.dest_key = req.dest_key;
            wrapper->ctx.caller_id = req.caller_id;
            if (wrapper->preCall())
            {
                wrapper->preReturn();
                return;
            }
            mtx.unlock();
        }
        else if (next != req.dest_id)
        {
            mtx.lock();
            wrapper->ctx.isRO = req.isRO;
            wrapper->ctx.request_id = req.id;
            wrapper->ctx.dest_id = req.dest_id;
            wrapper->ctx.dest_key = req.dest_key;
            wrapper->ctx.caller_id = req.caller_id;
            wrapper->ctx.visited.insert(next);
            allWrappers[next]->ctx = wrapper->ctx;
            mtx.unlock();
        }
        else
        {
            mtx.lock();
            wrapper->ctx.isRO = req.isRO;
            wrapper->ctx.request_id = req.id;
            wrapper->ctx.dest_id = req.dest_id;
            wrapper->ctx.dest_key = req.dest_key;
            wrapper->ctx.caller_id = req.caller_id;
            wrapper->ctx.visited.insert(next);
            allWrappers[next]->ctx = wrapper->ctx;
            allWrappers[next]->preRead(req.dest_key);
            allWrappers[next]->preReturn();
            mtx.unlock();
        }
    }
}