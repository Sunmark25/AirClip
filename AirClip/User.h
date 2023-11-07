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
    std::string userID;
    std::string username;
    std::string fullName;
    std::vector<Device*> activeDevices;
    std::vector<std::thread> activeDeviceThreads;

public:
    /**
     * The constructor for User
     *
     * @param userID The user's ID in the database
     * @param username The username for the user
     */
    User(const std::string userID, const std::string username, const std::string fullName) {
        this->userID = userID;
        this->username = username;
        this->fullName = fullName;
    }

    /**
     * This getter method is used to get the user's ID
     * @return The user's ID
     */
    std::string getUserID();

    /**
     * This getter method is used to get the user's username
     * @return The user's username
     */
    std::string getUsername();

    /**
     * This getter method is used to get the user's full name
     * @return The user's full name
     */
    std::string getFullName();

    /**
     * This method is used to connect a device for the user. It is responsible for
     * creating a new device and thread and storing both in the lists
     * @param wtConnectionId The wt connection ID (for sure's device web page) that corresponds to the user's device
     */
    void connectDevice(const std::string &wtConnectionId);
};

#endif // USER_H
