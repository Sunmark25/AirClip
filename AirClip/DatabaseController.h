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
    static DatabaseController *dbInstance_;
    static std::mutex mutex_;

    // Static callback function that matches the signature expected by sqlite3_exec
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * The DatabaseController's constructor/destructor should always be protected to
 * prevent direct construction/desctruction calls with the `new`/`delete`
 * operator.
 */
protected:
    // Constructor
    explicit DatabaseController(const char *filename) : db(nullptr), zErrMsg(nullptr) {
        int rc = sqlite3_open(filename, &db);
        if (rc) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            exit(0);
        } else {
            std::cout << "Opened database successfully" << std::endl;
        }

        initializeDatabase(); // Initializes the database if required (creates it and adds tables)
    }

    // Destructor
    ~DatabaseController() {
        sqlite3_close(db); // TODO: This might need to be called else where (or add a method added to close it)
    }

public:
    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field and you can provided an empty string for
     * the file name.
     */
    static DatabaseController *getInstance(const char *filename);

    // Member functions
    void createTable();

    bool sqlOperation(const std::string &sql);


    // Using prepared statements for efficiency, easier replacements and security (prevents SQL injection):
    // https://stackoverflow.com/questions/61794729/how-does-prepared-statements-in-sqlite-c-work'
    std::vector<std::vector<std::string>> selectData(const std::string &sql);


    void showTables();

    static bool tableIsEmpty(const std::vector<std::vector<std::string>> &tableData);

    void initializeDatabase();

    // Prevent copying or moving the database object.
    DatabaseController(const DatabaseController &) = delete;

    DatabaseController &operator=(const DatabaseController &) = delete;

    DatabaseController(DatabaseController &&) = delete;

    DatabaseController &operator=(DatabaseController &&) = delete;
};

#endif // DATABASECONTROLLER_H
