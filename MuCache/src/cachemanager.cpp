#include "wrapper.h"
#include "cachemanager.h"
#include "service.h"

extern std::map<int, CacheManager *> allCMs;
extern std::map<int, Wrapper *> allWrappers;
extern std::map<int, Service *> allServices;
std::map<int, std::set<int>> saved;
std::vector<std::pair<bool, int>> history;

CacheManager::CacheManager(int service_id_) : service_id(service_id_) {}

void CacheManager::startHandler(int request_id)
{
    history.push_back({true, request_id});
}

void CacheManager::endHandler(int caller_id, int request_id, std::set<int> rs)
{
    int flag = 0;
    for (int i = 0; i < history.size(); i++)
    {
        if (history[i].first && history[i].second == request_id)
        {
            flag = i;
            break;
        }
    }
    bool empty = true;
    for (int i = flag + 1; i < history.size(); i++)
    {
        for (int j : rs)
        {
            if (history[i].first == false && history[i].second == j)
            {
                empty = false;
                break;
            }
        }
    }
    if (empty)
    {
        int k = allWrappers[service_id]->ctx.dest_key;
        allServices[caller_id]->wrapper->save(k, allServices[service_id]->content[k]);
        saved[k].insert(caller_id);
    }
}

void CacheManager::invHandler(int key)
{
    history.push_back({false, key});
    if (saved.find(key) == saved.end())
        return;
    for (int i : saved[key])
    {
        allServices[i]->cache[key].first = false;
    }
    saved.erase(key);
}