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
    std::string password;
    std::vector<Device*> activeDevices;
    std::vector<std::thread> activeDeviceThreads;

public:
    /**
     * The constructor for User
     *
     * @param userID The user's ID in the database
     * @param username The username for the user
     */
    User(const std::string userID, const std::string username, const std::string password) {
        this->userID = userID;
        this->username = username;
        this->password = password;
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
     * This getter method is used to get the user's password
     * @return The user's password
     */
    std::string getPassword();

    /**
     * This method is used to connect a device for the user. It is responsible for
     * creating a new device and thread and storing both in the lists
     * @param wtConnectionId The wt connection ID (for sure's device web page) that corresponds to the user's device
     */

    Device *connectDevice();
};

#endif // USER_H
