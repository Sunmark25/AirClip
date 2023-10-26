#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <string>
#include  // Include the appropriate header for DatabaseConnection

class DatabaseController {
private:
    //TODO: implement SQL here as the database
 //   DatabaseConnection connection;

    // Method to establish a connection to the database
    void connectToDatabase();

public:
    DatabaseController(const std::string& databasePath);

    // Method to close the database connection
    void closeDatabaseConnection();

    // Method to retrieve the database connection
 //   DatabaseConnection getConnection();
};

#endif // DATABASECONTROLLER_H
