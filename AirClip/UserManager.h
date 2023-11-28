#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <vector>
#include <string>
#include <iostream>
#include "User.h"
#include "DatabaseController.h"

class UserManager {
private:
    std::vector<User> activeUsers;
    DatabaseController *dbc; // Store a reference to the database controller singleton

public:
    explicit UserManager() {
        dbc = DatabaseController::getInstance();
    }

    std::string findUser(const std::string &username);

    bool authenticateUser(const std::string &username, const std::string &password);

    std::string registerUser(const std::string &username, const std::string &password);

    Device* finishUserLogIn(const std::string &userID, const std::string &wtConnectionId, const std::string &username);

    std::string getPassword(const std::string &userID);
};

#endif // USERMANAGER_H
