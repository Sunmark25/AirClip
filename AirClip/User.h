//
// Created by Tingrui Zhang on 2023-10-25.
//

#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <thread>
#include "Device.h"

// Forward declaration of the Device class
class Device;

class User {
private:
    std::string userId;
    std::string userName;
    std::vector<Device> activeDevices;
    std::vector<std::thread> activeDeviceThreads;

public:
    User(std::string userId, std::string userName);

    // Getter method to retrieve the user's ID
    std::string getUserId();

    // Method to connect a device for the user
    void connectDevice();
};

#endif // USER_H
