//
// Created by Tingrui Zhang on 2023-10-25.
//

#include "User.h"

User::User(const std::string userId, const std::string userName) {
    this->userId = userId;
    this->userName = userName;
}

std::string User::getUserId() {
    return userId;
}

void User::connectDevice(const std::string &wtConnectionId) {
    // Create a newDevice and pass the wt connection ID
    auto newDevice = new Device(wtConnectionId);
    // Add the new device to the active devices
    activeDevices.emplace_back(newDevice);

    // Call createThead in Device to create a new thread for the device
    std::thread newDeviceThread = Device::createThread();
    // Add the thread to the active device threads
    activeDeviceThreads.push_back(std::move(newDeviceThread));
}
