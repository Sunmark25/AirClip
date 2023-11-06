#include "DatabaseController.h"

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

    const char *clipboardEntry = "CREATE TABLE IF NOT EXISTS CLIPBOARDENTRY (\n"
                                 "    clipboardEntryID VARCHAR(8) PRIMARY KEY CHECK (clipboardEntryID GLOB 'cl[0-9][0-9][0-9][0-9][0-9][0-9]'),\n"
                                 "    userID VARCHAR(6) NOT NULL UNIQUE CHECK (userID GLOB 'us[a-z][a-z][0-9][0-9]'),\n"
                                 "    content TEXT,\n"
                                 "    contentPath TEXT,\n"
                                 "    contentType TEXT NOT NULL,\n"
                                 "    CONSTRAINT contentType CHECK (contentT IN ('text', 'image', 'file')),\n"
                                 "    FOREIGN KEY (userID) REFERENCES AIRCLIP(userID)\n"
                                 "    );";
    int exec = sqlite3_exec(db, clipboardEntry, callback, 0, &zErrMsg);
    if (exec != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Table created successfully" << std::endl;
    }
}

void DatabaseController::insertSQL(const char *sql) {
    int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Insert successfully" << std::endl;
    }
}

void DatabaseController::selectSQL(const char *sql) {
    int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Select successfully" << std::endl;
    }
}

void DatabaseController::updateSQL(const char *sql) {
    int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Update successfully" << std::endl;
    }
}

void DatabaseController::deleteSQL(const char *sql) {
    int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Delete successfully" << std::endl;
    }
}


