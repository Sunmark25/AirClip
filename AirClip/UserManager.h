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
        //dbc.
    }

    /**
     * This method is used to find a user in the database and return their userId if they exist
     *
     * @param userName The username of the user to find in the database
     * @return The userId for the user if they exist, otherwise it returns an empty string
     */
    std::string findUser(const std::string &userName);

    /**
     * This method is used to authenticate a user by checking if
     * their given username and password match in the database
     *
     * @param userName The username provided by the user
     * @param password The password provided by the user
     * @return True if the user's credentials match, otherwise, it returns false
     */
    bool authenticateUser(const std::string &userName, const std::string &password);

    /**
     * This method is used to register a new user in the database using their username and password
     *
     * @param userName The username of the new user
     * @param password The password for the new user
     * @return The userId of the new user
     */
    std::string registerUser(const std::string &userName, const std::string &password);

    /**
     * This method is used to finish the login for the user by creating a User object
     * and connecting the device to the user
     *
     * @param userId The userId for the user being logged in
     * @param wtConnectionId The corresponding wt connection ID (for user's device web page) for the user's device
     * @param userName The username for the user being logged in
     */
    void finishUserLogIn(const std::string &userId, const std::string &wtConnectionId, const std::string &userName);
};

#endif // USERMANAGER_H
