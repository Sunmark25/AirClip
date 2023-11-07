#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <string>
#include <sqlite3.h>
#include <iostream>


class DatabaseController {
private:
    sqlite3 *db;
    char *zErrMsg;

    // Required for the singleton to be thread safe
    static DatabaseController * pinstance_;
    static std::mutex mutex_;

    // Static callback function that matches the signature expected by sqlite3_exec
    static int callback(void* NotUsed, int argc, char** argv, char** azColName);

/**
 * The DatabaseController's constructor/destructor should always be protected to
 * prevent direct construction/desctruction calls with the `new`/`delete`
 * operator.
 */
protected:
    // Constructor
    explicit DatabaseController(const char* filename) : db(nullptr), zErrMsg(nullptr) {
        int rc = sqlite3_open(filename, &db);
        if(rc) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            exit(0);
        } else {
            std::cout << "Opened database successfully" << std::endl;
        }

        value_ = filename;
    }

    // Destructor
    ~DatabaseController() {
        sqlite3_close(db);
    }

    std::string value_;

public:
    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */
    static DatabaseController *GetInstance(const char* filename);

    // Member functions
    void createTable();
    bool insertSQL(const std::string &sql);
    void selectSQL(const std::string &sql);
    std::vector<std::vector<std::string>> selectData(const std::string &sql);
    void updateSQL(const std::string &sql);
    void deleteSQL(const std::string &sql);
    void showTables();
    static bool isTableEmpty(const std::vector<std::vector<std::string>> &tableData);

    // TODO: Remove
    std::string value() const{
        return value_;
    }

    // Prevent copying or moving the database object.
    DatabaseController(const DatabaseController&) = delete;
    DatabaseController& operator=(const DatabaseController&) = delete;
    DatabaseController(DatabaseController&&) = delete;
    DatabaseController& operator=(DatabaseController&&) = delete;
};

#endif // DATABASECONTROLLER_H
