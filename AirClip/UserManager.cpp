#include "UserManager.h"
#include "DatabaseController.h"


std::string UserManager::findUser(const std::string &username) {
    // Define the query to find a user based on their user ID
    std::string query = "SELECT userID FROM User WHERE username = '" + username + "';";

    // Look for the userID matching the username
    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);

    // If the userID was found (the table wasn't empty) then return the userID
    if (!DatabaseController::tableIsEmpty(tableData)) {
        std::string userID = tableData[0][0];

        std::cout << "User ID: " << userID << std::endl;

        return userID;
    } else { // Otherwise, return an empty string
        std::cout << "No match for username" << std::endl;

        return "";
    }
}

std::string UserManager::getPassword(const std::string &userID) {
    // Define the query to find a user based on their user ID
    std::string query = "SELECT password FROM User WHERE userID = '" + userID + "';";

    // Look for the password matching the userID
    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);

    // If the password was found (the table wasn't empty) then return it
    if (!DatabaseController::tableIsEmpty(tableData)) {
        std::string password = tableData[0][2];

        std::cout << "Encrypted Password: " << password << std::endl;

        return password;
    } else { // Otherwise, return an empty string
        std::cout << "No match for userID" << std::endl;

        return "";
    }
}

bool UserManager::authenticateUser(const std::string &username, const std::string &password) {
    // Define the query to authenticate a user based on the given username and password
    std::string query =
            "SELECT userID FROM User WHERE username = '" + username + "' AND password = '" + password + "';";

    // Look for the user matching the credentials
    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);

    // If the there was a user found (the table wasn't empty) then return true
    if (!DatabaseController::tableIsEmpty(tableData)) {
        std::cout << "Matching login credentials for " << username << "found" << std::endl;

        return true;
    } else { // Otherwise, display a failure message and return false
        std::cout << "No matching login credentials" << std::endl;

        return false;
    }
}


std::string UserManager::registerUser(const std::string &username, const std::string &password) {
    // Define the query to add a new user with the given username and password
    std::string query =
            "INSERT INTO User ('username', 'password') VALUES ('" + username + "', '" + password + "');";

    // Try to add (insert) the new user in the database
    bool success = dbc->sqlOperation(query);

    // If the SQL query completed then return the user's ID
    if (success) {
        std::cout << "Success" << std::endl;
        return findUser(username);
    } else { // Otherwise, return an empty string
        std::cout << "Unable to add a new user in the database" << std::endl;
        return "";
    }
}

//TODO: Test this with real wtConnectionId
Device* UserManager::finishUserLogIn(const std::string &userID, const std::string &wtConnectionId,
                                  const std::string &username) {

    const std::string password = getPassword(userID);

    // Create a new user with the given userID, username and full name
    auto newUser = new User(userID, username, password);

    // Connect the device to the user
    return newUser->connectDevice(wtConnectionId);
}
