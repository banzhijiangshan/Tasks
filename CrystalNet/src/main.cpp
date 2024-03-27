#include <iostream>
#include <fstream>
#include <cstring>
#include "device.h"
#include "network.h"

int main(int argc, char *argv[])
{
    Network network;
    std::ifstream fin(argv[1]);
    int numDevices, numConnections;
    fin >> numDevices >> numConnections;
    for (int i = 0; i < numDevices; i++)
    {
        network.devices.push_back(Device(i + 1));
    }
    for (int i = 0; i < numConnections; i++)
    {
        int a, b;
        fin >> a >> b;
        network.devices[a - 1].upperConnectedDevices.push_back(b);
    }
    int numInputDevices;
    fin >> numInputDevices;
    for (int i = 0; i < numInputDevices; i++)
    {
        int a;
        fin >> a;
        network.inputDevices.push_back(a);
    }
    network.findSafeBoundary();
    for (int i : network.allEmulatedDevices)
    {
        std::cout << i << " ";
    }
    return 0;
}