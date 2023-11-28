#include "DeviceInfo.h"


std::string DeviceInfo::getDeviceId() const {
    return deviceId;
}

std::string DeviceInfo::getWtConnectionId() const {
    return wtConnectionId;
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

void DeviceInfo::setWtConnectionId(const std::string &value) {
    wtConnectionId = value;
}

void DeviceInfo::setDeviceName(const std::string &value) {
    deviceName = value;
}

void DeviceInfo::setNetworkAddress(const std::string &value) {
    networkAddress = value;
}

bool DeviceInfo::updateDeviceInfo(const DeviceInfo& newInfo) {
    setDeviceId(newInfo.getDeviceId());
    setWtConnectionId(newInfo.getWtConnectionId());
    setDeviceName(newInfo.getDeviceName());
    setNetworkAddress(newInfo.getNetworkAddress());
    return true;
}