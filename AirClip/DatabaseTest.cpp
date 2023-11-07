//
// Created by Jarrett Boersen on 2023-11-05.
//

#include "DatabaseController.h"

int main() {
    // Connect to the database
    auto dbc = new DatabaseController("../../AirClip.sqlite");

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

    query = "SELECT userId FROM User WHERE username = 'jboersen3';";

    tableData = dbc->selectData(query);

    if (!tableData.empty() && !tableData[0].empty()) {
        // Use a select statement to get userid from the database using userName
        std::string userId = tableData[0][0];

        std::cout << "User ID: " << userId << std::endl;
    } else {
        std::cout << "No match for username" << std::endl;
    }

    // ---- Get the userId using the username and password ----

    query = "SELECT userId FROM User WHERE username = 'jboersen' AND password = 'Password123!';";

    tableData = dbc->selectData(query);

    if (!tableData.empty() && !tableData[0].empty()) {
        // Use a select statement to get userid from the database using userName
        std::string userId = tableData[0][0];

        std::cout << "User ID: " << userId << std::endl;
    } else {
        std::cout << "No match for login credentials" << std::endl;
    }

    // ---- Insert a new user ----

    query = "INSERT INTO User ('username', 'password') VALUES ('jboersen3', 'Test');";

    bool success = dbc->insertSQL(query);

    if (success) {
        std::cout << "Success" << std::endl;
    } else {
        std::cout << "Fail" << std::endl;
    }
}
