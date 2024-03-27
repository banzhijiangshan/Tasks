#include "network.h"
#include <cstdlib>
#include <queue>

Network::Network()
{
    devices.reserve(256);
    inputDevices.reserve(64);
    allEmulatedDevices.reserve(64);
}

void Network::findSafeBoundary()
{
    std::queue<int> q;
    for (int i : inputDevices)
    {
        q.push(i);
        allEmulatedDevices.push_back(i);
    }
    bool visit[257];
    memset(visit, 0, sizeof(visit));
    while (!q.empty())
    {
        int id = q.front();
        q.pop();
        for (int i : devices[id - 1].upperConnectedDevices)
        {
            if (!visit[i])
            {
                visit[i] = true;
                q.push(i);
                allEmulatedDevices.push_back(i);
            }
        }
    }
}