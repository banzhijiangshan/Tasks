#ifndef MANAGER_H
#define MANAGER_H

#include <map>
#include <set>
#include <vector>

extern std::map<int, std::set<int>> saved;        // key to service_ids who saved it
extern std::vector<std::pair<bool, int>> history; // request_id = false, Inv_key = true

class CacheManager
{
public:
    int service_id;

    CacheManager(int service_id_);
    void startHandler(int request_id);
    void endHandler(int caller_id, int request_id, std::set<int> rs);
    void invHandler(int key);
};

#endif