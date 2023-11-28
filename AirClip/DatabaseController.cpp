#include "DatabaseController.h"

// Required for the singleton to be thread safe
DatabaseController *DatabaseController::dbInstance_{nullptr};
std::mutex DatabaseController::mutex_;

/**
 * The first time we call getInstance we will lock the storage location
 * and then we make sure again that the variable is null and then we
 * set the value.
 */
DatabaseController *DatabaseController::getInstance(const char *filename) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (dbInstance_ == nullptr) {
        dbInstance_ = new DatabaseController(filename);
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
        std::cout << "Table created successfully" << std::endl;
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
        std::cout << "Table created successfully" << std::endl;
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
        std::cout << "Table created successfully" << std::endl;
    }
}

bool DatabaseController::sqlOperation(const std::string &sql){
    int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return false;
    } else {
        std::cout << "Operation successfully" << std::endl;
        return true;
    }
}


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
    } else { // Otherwise, display there are no errors
        std::cout << "No errors in select statement" << std::endl;
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

void DatabaseController::showTables() {
    std::string sql = "SELECT name FROM sqlite_master\n"
                      "WHERE type='table'\n"
                      "ORDER BY name;";

    sqlOperation(sql); // Call the sqlOperation method to show the tables
}

bool DatabaseController::tableIsEmpty(const std::vector<std::vector<std::string>> &tableData) {
    // Return true if the row vector and column 0 vector are empty, otherwise, return false
    if (tableData.empty()) {
        return true;
    } else {
        return tableData[0].empty();
    }
}

void DatabaseController::initializeDatabase() {
    std::string sql = "SELECT name FROM sqlite_master\n"
                      "WHERE type='table'\n"
                      "AND name = 'User';";

    bool tableUserExists = !tableIsEmpty(selectData(sql));

    sql = "SELECT name FROM sqlite_master\n"
          "WHERE type='table'\n"
          "AND name = 'CLIPBOARDENTRY';";

    bool tableClipboardEntryExists = !tableIsEmpty(selectData(sql));

    sql = "SELECT name FROM sqlite_master\n"
          "WHERE type='table'\n"
          "AND name = 'Device';";

    bool tableDeviceExists = !tableIsEmpty(selectData(sql));

    if (!tableUserExists || !tableClipboardEntryExists || !tableDeviceExists) {
        createTable();
    }
}