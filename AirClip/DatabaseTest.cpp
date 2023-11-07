//
// Created by Jarrett Boersen on 2023-11-05.
//

// TODO: Remove?

#include "DatabaseController.h"

int main() {
    // Connect to the database
    DatabaseController* dbc = DatabaseController::getInstance("../../AirClip.sqlite");

    // Show the tables in it
    dbc->showTables();

    // ---- Select the users ----

    std::string query = "SELECT * FROM User;";

    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);

    for (const auto& row : tableData) {
        for (const std::string& value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    // ---- Get the userId using the username ----

    query = "SELECT userID FROM User WHERE username = 'jboersen';";

    tableData = dbc->selectData(query);

    if (!tableData.empty() && !tableData[0].empty()) {
        // Use a select statement to get userid from the database using userName
        std::string userID = tableData[0][0];

        std::cout << "User ID for username: " << userID << std::endl;
    } else {
        std::cout << "No match for username" << std::endl;
    }

    // ---- Get the userId using the username and password ----

    query = "SELECT userID FROM User WHERE username = 'jboersen' AND password = 'Password123';";

    tableData = dbc->selectData(query);

    if (!tableData.empty() && !tableData[0].empty()) {
        // Use a select statement to get userid from the database using userName
        std::string userID = tableData[0][0];

        std::cout << "UserID for login credentials: " << userID << std::endl;
    } else {
        std::cout << "No match for login credentials" << std::endl;
    }

    // ---- Insert a new user ----

//    query = "INSERT INTO User ('username', 'password', 'fullName') VALUES ('tholland', 'not@home', 'Tom Holland');";
//
//    bool success = dbc->insertSQL(query);
//
//    if (success) {
//        std::cout << "Successfully added new user" << std::endl;
//    } else {
//        std::cout << "Failed to added new user" << std::endl;
//    }
}
