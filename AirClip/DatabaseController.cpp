#include "DatabaseController.h"

// TODO: Use prepared statements for efficiency, easier replacements and security (prevents SQL injection):
//  https://stackoverflow.com/questions/61794729/how-does-prepared-statements-in-sqlite-c-work'

// Example:
/*
void DatabaseController::showTables() {
    std::string colName = "name";
    std::string sql = "SELECT " + colName + " FROM sqlite_master\n"
                                            "WHERE type=?\n"
                                            "ORDER BY " + colName + ";";

    sqlite3_stmt* stmt;

    // Use prepare_v2 to execute the same SQL statement with different parameter values, or
    // to allow the use placeholders in the SQL statement for security (e.g., to prevent SQL injection).
    // Use c_str() to convert the string to a C string
    int rc = sqlite3_prepare_v2(
            db,             // the handle to your (opened and ready) database
            sql.c_str(),    // the sql statement, utf-8 encoded
            sql.length(),   // max length of sql statement
            &stmt,          // this is an "out" parameter, the compiled statement goes here
            nullptr);       // pointer to the tail end of sql statement (when there are
    // multiple statements inside the string; can be null)
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    }

    std::string type = "table";
    // Replaces ?
    sqlite3_bind_text(
            stmt,               // previously compiled prepared statement object
            1,                  // parameter index, 1-based
            type.c_str(),       // the data
            type.length(),      // length of data
            SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* tableName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::cout << "Table Name: " << tableName << std::endl;
    }

    sqlite3_finalize(stmt);
}
 */

// Required for the singleton to be thread safe
DatabaseController* DatabaseController::pInstance_{nullptr};
std::mutex DatabaseController::mutex_;

/**
 * The first time we call getInstance we will lock the storage location
 * and then we make sure again that the variable is null and then we
 * set the value.
 */
DatabaseController *DatabaseController::getInstance(const char* filename)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pInstance_ == nullptr)
    {
        pInstance_ = new DatabaseController(filename);
    }
    return pInstance_;
}

// Callback function definition
int DatabaseController::callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for(int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

void DatabaseController::createTable(){
    const char *sql = "CREATE TABLE IF NOT EXISTS AIRCLIP (\n"
                      "    userName TEXT NOT NULL,\n"
                      "    userID VARCHAR(6) PRIMARY KEY CHECK (userID GLOB 'us[a-z][a-z][0-9][0-9]'),\n"
                      "    deviceID VARCHAR(6) NOT NULL UNIQUE CHECK (deviceID GLOB 'de[a-z][a-z][0-9][0-9]'),\n"
                      "    deviceName TEXT NOT NULL\n"
                      ");";
    int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Table created successfully" << std::endl;
    }
}

bool DatabaseController::insertSQL(const std::string &sql) {
    int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return false; // Return false because the insert failed
    } else {
        std::cout << "Insert successfully" << std::endl;
        return true; // Return true because the insert succeeded
    }
}

void DatabaseController::selectSQL(const std::string &sql) {
    // Use c_str() to convert the string to a C string
    int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Select successfully" << std::endl;
    }
}

std::vector<std::vector<std::string>> DatabaseController::selectData(const std::string &sql) {
    // Store the table rows and columns data (Get like so [row][column])
    std::vector<std::vector<std::string>> resultData;

    // Used to store the prepared statement
    sqlite3_stmt* stmt;

    // Prepare the select statement call to the database using the sql query
    // Use c_str() to convert the string to a C string
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    // If the statement had an error display it and return early (with an empty vector set)
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return resultData;
    } else { // Otherwise, display it completed successfully
        std::cout << "Select successfully" << std::endl;
    }

    // Loop through each row
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Get the number of columns in the row
        int numColumns = sqlite3_column_count(stmt);
        // Used to store the  row's data
        std::vector<std::string> rowData;

        // Loop through each column and add the value as a string to the row
        for (int i = 0; i < numColumns; i++) {
            const char* columnValue = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            rowData.emplace_back(columnValue);
        }

        // Add the row to the table's data
        resultData.push_back(rowData);
    }

    // Free the statement and return with the table data
    sqlite3_finalize(stmt);
    return resultData;
}

void DatabaseController::updateSQL(const std::string &sql) {
    int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Update successfully" << std::endl;
    }
}

void DatabaseController::deleteSQL(const std::string &sql) {
    int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Delete successfully" << std::endl;
    }
}

void DatabaseController::showTables() {
    std::string sql = "SELECT name FROM sqlite_master\n"
                      "WHERE type='table'\n"
                      "ORDER BY name;";

    selectSQL(sql); // Call the selectSQL method to show the tables
}

bool DatabaseController::isTableEmpty(const std::vector<std::vector<std::string>> &tableData) {
    // Return true if the row vector and column 0 vector are not empty, otherwise, return false
    return !tableData.empty() && !tableData[0].empty();
}