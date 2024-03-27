#include "wrapper.h"
#include "cachemanager.h"
#include "service.h"

std::map<int, std::set<int>> readset;
extern std::map<int, CacheManager *> allCMs;
extern std::map<int, Wrapper *> allWrappers;
extern std::map<int, Service *> allServices;
extern int path[10][10];

Wrapper::Wrapper(int service_id_) : service_id(service_id_) {}

void Wrapper::preStart()
{
    readset.insert({ctx.request_id, {}});
    allCMs[service_id]->startHandler(ctx.request_id);
}

void Wrapper::preRead(int k)
{
    readset[ctx.request_id].insert(k);
    Read();
    std::cout << "Request " << ctx.request_id << " from service " << ctx.caller_id << " reads key " << k << " on service " << ctx.dest_id << " with value " << allServices[ctx.dest_id]->content[k] << std::endl;
}

void Wrapper::Read()
{
    sleep(1);
}

void Wrapper::save(int k, int v)
{
    allServices[service_id]->cache[k] = std::make_pair(1, v);
}

void Wrapper::preReturn()
{
    std::set<int> rs = readset[ctx.request_id];
    readset.erase(ctx.request_id);
    int caller_id = ctx.caller_id;
    allCMs[ctx.dest_id]->endHandler(caller_id, ctx.request_id, rs);
}

void Wrapper::postWrite(int k, int v)
{
    allServices[ctx.dest_id]->content[k] = v;
    ctx.visited.insert(ctx.dest_id);
    sleep(1);
    std::cout << "Request " << ctx.request_id << " from service " << ctx.caller_id << " writes key " << k << " on service " << ctx.dest_id << " with a new value " << v << std::endl;
    allCMs[service_id]->invHandler(k);
}

bool Wrapper::preCall()
{
    if (ctx.isRO && ctx.visited.find(ctx.dest_id) == ctx.visited.end()) // address diamond pattern
    {
        if (allServices[service_id]->cache.find(ctx.dest_key) != allServices[service_id]->cache.end())
        {
            if (allServices[service_id]->cache[ctx.dest_key].first)
            {
                std::cout << "Request" << ctx.request_id << " hits cache" << std::endl;
                return true;
            }
        }
    }
    else if (ctx.isRO)
    {
        std::cout << "Request" << ctx.request_id << " cache miss" << std::endl;
    }
    return false;
}