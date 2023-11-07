#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <string>
#include <sqlite3.h>
#include <iostream>


class DatabaseController {
private:
    sqlite3 *db;
    char *zErrMsg;

    // Static callback function that matches the signature expected by sqlite3_exec
    static int callback(void* NotUsed, int argc, char** argv, char** azColName);

public:
    // Constructor
    explicit DatabaseController(const char* filename) : db(nullptr), zErrMsg(nullptr) {
        int rc = sqlite3_open(filename, &db);
        if(rc) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            exit(0);
        } else {
            std::cout << "Opened database successfully" << std::endl;
        }
    }

    // Destructor
    ~DatabaseController() {
        sqlite3_close(db);
    }

    // Member functions
    void createTable();
    bool insertSQL(const std::string &sql);
    void selectSQL(const std::string &sql);
    std::vector<std::vector<std::string>> selectData(const std::string &sql);
    void updateSQL(const std::string &sql);
    void deleteSQL(const std::string &sql);
    void showTables();
    static bool isTableEmpty(const std::vector<std::vector<std::string>> &tableData);

    // Prevent copying or moving the Database object.
    DatabaseController(const DatabaseController&) = delete;
    DatabaseController& operator=(const DatabaseController&) = delete;
    DatabaseController(DatabaseController&&) = delete;
    DatabaseController& operator=(DatabaseController&&) = delete;
};

#endif // DATABASECONTROLLER_H
