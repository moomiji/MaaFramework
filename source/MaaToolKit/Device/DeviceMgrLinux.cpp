#if defined(__linux__)

#include "DeviceMgrLinux.h"

#include <tuple> // for std::ignore

MAA_TOOLKIT_DEVICE_NS_BEGIN

std::vector<Device> DeviceMgrLinux::find_device_impl(std::string_view specified_adb)
{
    // TODO
    std::ignore = specified_adb;
    return {};
}

MAA_TOOLKIT_DEVICE_NS_END

#endif