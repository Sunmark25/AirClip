//
// Created by Tingrui Zhang on 2023-10-25.
//

#include "DeviceInfo.h"


string DeviceInfo::getDeviceId() const {
    return deviceId;
}

string DeviceInfo::getWtConnectionId() const {
    return wtConnectionId;
}

string DeviceInfo::getDeviceType() const {
    return deviceType;
}

string DeviceInfo::getNetworkAddress() const {
    return networkAddress;
}

void DeviceInfo::setDeviceId(const string &value) {
    deviceId = value;
}

void DeviceInfo::setWtConnectionId(const string &value) {
    wtConnectionId = value;
}

void DeviceInfo::setDeviceType(const string &value) {
    deviceType = value;
}

void DeviceInfo::setNetworkAddress(const string &value) {
    networkAddress = value;
}

bool DeviceInfo::updateDeviceInfo(const DeviceInfo& newInfo) {
    setDeviceId(newInfo.getDeviceId());
    setWtConnectionId(newInfo.getWtConnectionId());
    setDeviceType(newInfo.getDeviceType());
    setNetworkAddress(newInfo.getNetworkAddress());
    return true;
}