#include "device.h"

Device::Device(int id_) : id(id_)
{
    upperConnectedDevices.reserve(10);
}
