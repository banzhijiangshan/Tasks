#include "wrapper.h"
#include "service.h"
#include "cachemanager.h"
#include "request.h"
#include <iostream>
#include <fstream>
#include <map>
#include <thread>

std::map<int, Wrapper *> allWrappers;
std::map<int, CacheManager *> allCMs;
std::map<int, Service *> allServices;
int path[10][10];
bool service[10][10];
int dis[10][10];

int main(int argc, char *argv[])
{
    int serviceNum, connect;
    std::ifstream fin(argv[1]);
    fin >> serviceNum >> connect;
    for (int i = 0; i < connect; i++)
    {
        int a, b;
        fin >> a >> b;
        service[a][b] = 1;
        service[b][a] = 1;
    }

    for (int i = 1; i <= serviceNum; i++)
    {
        for (int j = 1; j <= serviceNum; j++)
        {
            if (i == j)
            {
                dis[i][j] = 0;
                path[i][j] = i;
                continue;
            }
            if (service[i][j])
            {
                dis[i][j] = 1;
                path[i][j] = i;
            }
            else
            {
                dis[i][j] = 999999;
                path[i][j] = -1;
            }
        }
    }
    for (int k = 1; k <= serviceNum; k++)
    {
        for (int i = 1; i <= serviceNum; i++)
        {
            for (int j = 1; j <= serviceNum; j++)
            {
                if (dis[i][j] > dis[i][k] + dis[k][j])
                {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }

    for (int i = 1; i <= serviceNum; i++)
    {
        allCMs[i] = new CacheManager(i);
        allWrappers[i] = new Wrapper(i);
        allServices[i] = new Service(i, allWrappers[i], allCMs[i]);
        allServices[i]->content.insert({2 * i - 1, 999 - (2 * i - 1)});
        allServices[i]->content.insert({2 * i, 999 - 2 * i});
        // insert key-value pairs, the key and value are both arbitrarily chosen
    }

    Request r1 = Request(1, 1, 4, 7, false, 666);
    Request r2 = Request(2, 1, 4, 8, true, 0);

    std::thread t1(&Service::handleRequest, allServices[1], r1);
    std::thread t2(&Service::handleRequest, allServices[1], r2);
    t1.join();
    t2.join();
    return 0;
}