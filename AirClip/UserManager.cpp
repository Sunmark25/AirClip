//
// Created by Tingrui Zhang on 2023-10-25.
//

#include "UserManager.h"
#include "DatabaseController.h"


std::string UserManager::findUser(const std::string &userName) {
    // Define the query to find a user based on their user ID
    std::string query = "SELECT userId FROM User WHERE username = '" + userName + "';";

    // Look for the userId matching the username
    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);

    // If the userId was found (the table wasn't empty) then return the userId
    if (!DatabaseController::isTableEmpty(tableData)) {
        std::string userId = tableData[0][0];

        std::cout << "User ID: " << userId << std::endl;

        return userId;
    } else { // Otherwise, return an empty string
        std::cout << "No match for username" << std::endl;

        return "";
    }
}

bool UserManager::authenticateUser(const std::string &userName, const std::string &password) {
    // Define the query to authenticate a user based on the given username and password
    std::string query = "SELECT userId FROM User WHERE username = '" + userName + "' AND password = '" + password + "';";

    // Look for the user matching the credentials
    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);

    // If the there was a user found (the table wasn't empty) then return true
    if (!DatabaseController::isTableEmpty(tableData)) {
        std::cout << "Matching login credentials for " << userName << "found" << std::endl;

        return true;
    } else { // Otherwise, display a failure message and return false
        std::cout << "No matching login credentials" << std::endl;

        return false;
    }
}

std::string UserManager::registerUser(const std::string &userName, const std::string &password) {
    // Define the query to add a new user with the given username and password
    std::string query = "INSERT INTO User ('username', 'password') VALUES ('" + userName + "', '" + password + "');";

    // Try to add (insert) the new user in the database
    bool success = dbc->insertSQL(query);

    // If the SQL query completed then return the user's ID
    if (success) {
        std::cout << "Success" << std::endl;
        return findUser(userName);
    } else { // Otherwise, return an empty string
        std::cout << "Unable to add a new user in the database" << std::endl;
        return "";
    }
}

void UserManager::finishUserLogIn(const std::string &userId, const std::string &wtConnectionId, const std::string &userName) {
    // Create a new user with the given userId and username
    auto newUser = new User(userId, userName);

    // Connect the device to the user
    newUser->connectDevice(wtConnectionId);
}
