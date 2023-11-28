/**
 * @class UserManager
 * @brief Manages user-related operations in the application.
 *
 * The UserManager class provides functionalities for finding, authenticating,
 * registering, and logging in users within the application. It interacts with
 * a database through the DatabaseController.
 */

#include "UserManager.h"
#include "DatabaseController.h"

/**
 * @brief Finds a user by username and returns their userID.
 *
 * This method queries the database to find the userID associated with the given username.
 * If the username exists in the database, it returns the userID; otherwise, it returns an empty string.
 *
 * @param username The username of the user to be found.
 * @return std::string The userID if found, otherwise an empty string.
 */
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

/**
 * @brief Retrieves the password for a user with the specified userID.
 *
 * This method queries the database for the password associated with the given userID.
 * It returns the password if found; otherwise, it returns an empty string.
 *
 * @note The returned password is encrypted.
 *
 * @param userID The unique identifier of the user.
 * @return std::string The encrypted password if found, otherwise an empty string.
 */
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

/**
 * @brief Authenticates a user based on their username and password.
 *
 * This method checks if the provided username and password match an existing user in the database.
 * It returns true if a match is found, indicating successful authentication.
 *
 * @param username The username of the user.
 * @param password The password of the user.
 * @return bool True if the user is authenticated, false otherwise.
 */
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

/**
 * @brief Registers a new user with a username and password.
 *
 * This method inserts a new user record into the database with the provided username and password.
 * It returns the userID of the newly created user or an empty string if the operation fails.
 *
 * @param username The username for the new user.
 * @param password The password for the new user.
 * @return std::string The userID of the newly registered user, or an empty string on failure.
 */
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

/**
 * @brief Finalizes user login and connects a device to the user.
 *
 * This method retrieves the password for the user with the given userID, creates a new User instance,
 * and connects a device to this user using the provided wtConnectionId.
 *
 * @param userID The userID of the user.
 * @param wtConnectionId The connection ID for the device.
 * @param username The username of the user.
 * @return Device* A pointer to the connected device, or nullptr on failure.
 */
//TODO: Test this with real wtConnectionId
Device* UserManager::finishUserLogIn(const std::string &userID, const std::string &wtConnectionId,
                                  const std::string &username) {

    const std::string password = getPassword(userID);

    // Create a new user with the given userID, username and full name
    auto newUser = new User(userID, username, password);

    // Connect the device to the user
    return newUser->connectDevice();
}
