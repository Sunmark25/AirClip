//
// Created by Tingrui Zhang on 2023-10-25.
//

#include "UserManager.h"

UserManager::UserManager() {
}

std::string UserManager::findUser(const std::string &userName) {
    // Use a select statement to get userid from the database using userName
    std::string userId = "temp01";

    // If the userId is not empty (or whatever the query would return)
    // then return the userId matching the userName
    if (!userId.empty()) {
        return userId;
    } else { // Otherwise, return an empty string
        return "";
    }
}

bool UserManager::authenticateUser(const std::string &userName, const std::string &password) {
    // Use a select statement to see if the username and password match the ones in the database
    std::string match = "some match";

    // If the userId is not empty (or whatever the query would return)
    // then return the userId matching the userName
    return !match.empty();
}

std::string UserManager::registerUser(const std::string &userName, const std::string &password) {
    // Do an insert query to add the user to the database (add their username and password)
    // The query should return the userId for the newly added user
    std::string userId = "temp02";

    return userId;
}

void UserManager::finishUserLogIn(const std::string &userId, const std::string &wtConnectionId, const std::string &userName) {
    // Create a new user with the given userId and username
    auto newUser = new User(userId, userName);

    // Connect the device to the user
    newUser->connectDevice(wtConnectionId);
}
