#ifndef NET_H
#define NET_H

#include <vector>
#include <string>
#include "device.h"

class Network
{
public:
    std::vector<Device> devices;
    std::vector<int> inputDevices;
    std::vector<int> allEmulatedDevices;

    Network();
    void findSafeBoundary();
};

#endif