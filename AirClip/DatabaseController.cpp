/**
 * @class DatabaseController
 * @brief Manages database operations for the application using SQLite.
 *
 * This class is a singleton that provides an interface to interact with a SQLite database.
 * It includes functionalities to create and initialize the database, execute SQL operations,
 * and retrieve data. It ensures that only one instance of the database controller exists
 * within the application at any time, providing a global point of access to the database.
 *
 * The class includes mechanisms to prevent copying or moving of the DatabaseController instance,
 * ensuring that accidental duplication of the database connection is avoided.
 *
 * @note The DatabaseController should be accessed via getInstance method to ensure the singleton pattern is maintained.
 */

#include "DatabaseController.h"

// Required for the singleton to be thread safe
DatabaseController *DatabaseController::dbInstance_{nullptr};
std::mutex DatabaseController::mutex_;

/**
 * @brief Provides access to the singleton instance of the DatabaseController.
 *
 * If the singleton instance does not exist, it is created. Otherwise, the existing instance is returned.
 *
 * @param filename The name of the SQLite database file. Provide an empty string if the instance already exists.
 * @return DatabaseController* The singleton instance of the DatabaseController.
 */
DatabaseController *DatabaseController::getInstance() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (dbInstance_ == nullptr) {
        dbInstance_ = new DatabaseController();
    }
    return dbInstance_;
}

// Callback function definition
int DatabaseController::callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

/**
 * @brief Creates a table in the database.
 *
 * The implementation details are not provided in the code snippet.
 */
void DatabaseController::createTable() {
    const char *userSQL = "CREATE TABLE IF NOT EXISTS User (\n"
                          "    userID INTEGER PRIMARY KEY AUTOINCREMENT,\n"
                          "    username TEXT NOT NULL UNIQUE,\n"
                          "    password TEXT NOT NULL\n"
                          "    );";

    int createUser = sqlite3_exec(db, userSQL, callback, 0, &zErrMsg);
    if (createUser != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "User Table created successfully" << std::endl;
    }

    const char *clipboardEntrySQL = "CREATE TABLE IF NOT EXISTS ClipboardEntry (\n"
                                    "    clipboardEntryID INTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                    "    timeAdded TEXT,\n"
                                    "    deviceID VARCHAR(6) NOT NULL,\n"
                                    "    userTag TEXT,\n"
                                    "    content TEXT,\n"
                                    "    contentPath TEXT\n"
                                    "    );";

    int createCE = sqlite3_exec(db, clipboardEntrySQL, callback, 0, &zErrMsg);
    if (createCE != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "ClipboardEntry Table created successfully" << std::endl;
    }

    const char *deviceSQL = "CREATE TABLE IF NOT EXISTS Device(\n"
                            "    deviceID INTEGER PRIMARY KEY AUTOINCREMENT,\n"
                            "    deviceName TEXT NOT NULL,\n"
                            "    userID VARCHAR(6) NOT NULL\n"
                            "    );";

    int createDevice = sqlite3_exec(db, deviceSQL, callback, 0, &zErrMsg);
    if (createDevice != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Device Table created successfully" << std::endl;
    }
}

/**
 * @brief Executes a SQL operation.
 *
 * This method is used to execute SQL commands that do not return data, such as INSERT, UPDATE, and DELETE.
 *
 * @param sql The SQL command to be executed.
 * @return bool True if the operation was successful, false otherwise.
 */
bool DatabaseController::sqlOperation(const std::string &sql) {
    int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return false;
    } else {
        return true;
    }
}

/**
 * @brief Executes a SELECT SQL operation and retrieves data.
 *
 * Uses prepared statements for efficiency and security. This method is suitable for SQL queries that retrieve data.
 *
 * @param sql The SQL SELECT command to be executed.
 * @return std::vector<std::vector<std::string>> A 2D vector containing the query results.
 */
std::vector<std::vector<std::string>> DatabaseController::selectData(const std::string &sql) {
    // Store the table rows and columns data (Get like so [row][column])
    std::vector<std::vector<std::string>> resultData;

    // Used to store the prepared statement
    sqlite3_stmt *stmt;

    // Prepare the select statement call to the database using the sql query
    // Use c_str() to convert the string to a C string
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    // If the statement had an error display it and return early (with an empty vector set)
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return resultData;
    }

    // Loop through each row
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Get the number of columns in the row
        int numColumns = sqlite3_column_count(stmt);
        // Used to store the  row's data
        std::vector<std::string> rowData;

        // Loop through each column and add the value as a string to the row
        for (int i = 0; i < numColumns; i++) {
            const char *columnValue = reinterpret_cast<const char *>(sqlite3_column_text(stmt, i));
            rowData.emplace_back(columnValue);
        }

        // Add the row to the table's data
        resultData.push_back(rowData);
    }

    // Free the statement and return with the table data
    sqlite3_finalize(stmt);
    return resultData;
}

/**
 * @brief Gets the tables present in the database.
 *
 * @return std::vector<std::string> A vector containing the tables.
 */
std::vector<std::string> DatabaseController::getTables() {
    std::string sql = "SELECT name FROM sqlite_master\n"
                      "WHERE type='table'\n"
                      "ORDER BY name;";

    std::vector<std::vector<std::string>> tables = selectData(sql); // Call the sqlOperation method to show the tables

    // Flatten the vector
    std::vector<std::string> flattenedVector;

    // Iterate through the outer vector and concatenate inner vectors
    for (const auto &innerVector: tables) {
        flattenedVector.insert(flattenedVector.end(), innerVector.begin(), innerVector.end());
    }

    return flattenedVector;
}

//bool DatabaseController::in_array(const std::string &value, const std::vector<std::string> &array) {
//    return std::find(array.begin(), array.end(), value) != array.end();
//}

/**
 * @brief Checks if the given table data is empty.
 *
 * @param tableData A 2D vector representing the table data.
 * @return bool True if the table is empty, false otherwise.
 */
bool DatabaseController::tableIsEmpty(const std::vector<std::vector<std::string>> &tableData) {
    // Return true if the row vector and column 0 vector are empty, otherwise, return false
    if (tableData.empty()) {
        return true;
    } else {
        return tableData[0].empty();
    }
}

/**
 * @brief Initializes the database with necessary tables and data.
 *
 * The implementation details are not provided in the code snippet.
 */
void DatabaseController::initializeDatabase() {
    std::string sql = "SELECT name FROM sqlite_master\n"
                      "WHERE type='table'\n"
                      "AND name = 'User';";

    bool tableUserExists = !tableIsEmpty(selectData(sql));

    sql = "SELECT name FROM sqlite_master\n"
          "WHERE type='table'\n"
          "AND name = 'ClipboardEntry';";

    bool tableClipboardEntryExists = !tableIsEmpty(selectData(sql));

    sql = "SELECT name FROM sqlite_master\n"
          "WHERE type='table'\n"
          "AND name = 'Device';";

    bool tableDeviceExists = !tableIsEmpty(selectData(sql));

    if (!tableUserExists || !tableClipboardEntryExists || !tableDeviceExists) {
        createTable();
    }
}

