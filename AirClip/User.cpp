#include "User.h"

std::string User::getUserID() {
    return userID;
}

std::string User::getUsername() {
    return username;
}

std::string User::getPassword() {
    return password;
}

/**
  * This method is used to connect a device for the user. It is responsible for
  * creating a new device and thread and storing both in the lists
  * @param wtConnectionId The wt connection ID (for sure's device web page) that corresponds to the user's device
  */
Device* User::connectDevice() {
    // Create a newDevice and pass the wt connection ID
    auto newDevice = new Device();
    // Add the new device to the active devices
    activeDevices.emplace_back(newDevice);

    return newDevice;
}
