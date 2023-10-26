#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <vector>
#include <string>
#include "User.h"

class UserManager {
private:
    std::vector<User> activeUsers;

public:
    UserManager();

    // Function to find a user by their username
    std::string findUser(std::string userName);

    // Function to authenticate a user
    bool authenticateUser(std::string userName, std::string password);

    // Function to register a new user
    std::string registerUser(std::string userName, std::string password);

    // Function to finish user login
    void finishUserLogIn(std::string userId, std::string wtConnectionId, std::string userName);
};

#endif // USERMANAGER_H
