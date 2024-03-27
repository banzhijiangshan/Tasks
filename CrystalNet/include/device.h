#ifndef DEVICE_H
#define DEVICE_H

#include <cstring>
#include <vector>

class Device
{
public:
    int id;
    std::vector<int> upperConnectedDevices;

    Device(int id_ = 0);
};

#endif