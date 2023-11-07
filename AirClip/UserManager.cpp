//
// Created by Tingrui Zhang on 2023-10-25.
//

#include "UserManager.h"
#include "DatabaseController.h"


std::string UserManager::findUser(const std::string &username) {
    // Define the query to find a user based on their user ID
    std::string query = "SELECT userID FROM User WHERE username = '" + username + "';";

    // Look for the userID matching the username
    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);

    // If the userID was found (the table wasn't empty) then return the userID
    if (!DatabaseController::isTableEmpty(tableData)) {
        std::string userID = tableData[0][0];

        std::cout << "User ID: " << userID << std::endl;

        return userID;
    } else { // Otherwise, return an empty string
        std::cout << "No match for username" << std::endl;

        return "";
    }
}

std::string UserManager::getFullName(const std::string &userID) {
    // Define the query to find a user based on their user ID
    std::string query = "SELECT fullName FROM User WHERE userID = '" + userID + "';";

    // Look for the fullName matching the userID
    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);

    // If the fullName was found (the table wasn't empty) then return it
    if (!DatabaseController::isTableEmpty(tableData)) {
        std::string fullName = tableData[0][0];

        std::cout << "Full name: " << fullName << std::endl;

        return fullName;
    } else { // Otherwise, return an empty string
        std::cout << "No match for userID" << std::endl;

        return "";
    }
}

bool UserManager::authenticateUser(const std::string &username, const std::string &password) {
    // Define the query to authenticate a user based on the given username and password
    std::string query = "SELECT userID FROM User WHERE username = '" + username + "' AND password = '" + password + "';";

    // Look for the user matching the credentials
    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);

    // If the there was a user found (the table wasn't empty) then return true
    if (!DatabaseController::isTableEmpty(tableData)) {
        std::cout << "Matching login credentials for " << username << "found" << std::endl;

        return true;
    } else { // Otherwise, display a failure message and return false
        std::cout << "No matching login credentials" << std::endl;

        return false;
    }
}

std::string UserManager::registerUser(const std::string &username, const std::string &password, const std::string &fullName) {
    // Define the query to add a new user with the given username and password
    std::string query = "INSERT INTO User ('username', 'password', 'fullName') VALUES ('" + username + "', '" + password + "', '" + fullName + "');";

    // Try to add (insert) the new user in the database
    bool success = dbc->insertSQL(query);

    // If the SQL query completed then return the user's ID
    if (success) {
        std::cout << "Success" << std::endl;
        return findUser(username);
    } else { // Otherwise, return an empty string
        std::cout << "Unable to add a new user in the database" << std::endl;
        return "";
    }
}

void UserManager::finishUserLogIn(const std::string &userID, const std::string &wtConnectionId, const std::string &username) {
    // Get the user's full name using their userID
    const std::string fullName = getFullName(userID);

    // Create a new user with the given userID, username and full name
    auto newUser = new User(userID, username, fullName);

    // Connect the device to the user
    newUser->connectDevice(wtConnectionId);
}
