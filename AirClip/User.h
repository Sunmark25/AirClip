
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

    std::string getUserID();
    std::string getUsername();
    std::string getFullName();


    void connectDevice(const std::string &wtConnectionId);
};

#endif // USER_H
