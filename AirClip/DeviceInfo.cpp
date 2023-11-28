/**
 * @class DeviceInfo
 * @brief This class encapsulates various properties of a device, such as its ID, connection ID, name, and network address.
 */

#include "DeviceInfo.h"


std::string DeviceInfo::getDeviceId() const {
    return deviceId;
}


std::string DeviceInfo::getDeviceName() const {
    return deviceName;
}

std::string DeviceInfo::getNetworkAddress() const {
    return networkAddress;
}

void DeviceInfo::setDeviceId(const std::string &value) {
    deviceId = value;
}


void DeviceInfo::setDeviceName(const std::string &value) {
    deviceName = value;
}

void DeviceInfo::setNetworkAddress(const std::string &value) {
    networkAddress = value;
}

/**
    * @brief Updates the device information.
    *
    * Updates the current device information with the details provided in the newInfo object.
    *
    * @param newInfo The new device information to be updated.
    * @return True if the update is successful, false otherwise.
    */
bool DeviceInfo::updateDeviceInfo(const DeviceInfo& newInfo) {
    setDeviceId(newInfo.getDeviceId());
    setDeviceName(newInfo.getDeviceName());
    setNetworkAddress(newInfo.getNetworkAddress());
    return true;
}