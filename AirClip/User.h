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
    std::vector<Device*> activeDevices;
    std::vector<std::thread> activeDeviceThreads;

public:
    /**
     * Constructor for User
     * @param userId The user's ID in the database
     * @param userName The username for the user
     */
    explicit User(std::string userId, std::string userName);

    /**
     * This getter method is used to get the user's ID
     * @return The user's ID
     */
    std::string getUserId();

    /**
     * This method is used to connect a device for the user. It is responsible for
     * creating a new device and thread and storing both in the lists
     * @param wtConnectionId The wt connection ID (for their web page) that corresponds to the user
     */
    void connectDevice(const std::string &wtConnectionId);
};

#endif // USER_H
