#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <string>
#include <sqlite3.h>
#include <iostream>
#include <mutex>
#include <vector>

class DatabaseController {
private:
    const char *FILENAME = "../../AirClip.sqlite";

    sqlite3 *db;   ///< Pointer to the SQLite database.
    char *zErrMsg; ///< Error message string used by SQLite.

    static DatabaseController *dbInstance_; ///< Static instance of the DatabaseController (singleton).
    static std::mutex mutex_; ///< Mutex to ensure thread safety for the singleton instance.

    // Static callback function that matches the signature expected by sqlite3_exec
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * The DatabaseController's constructor/destructor should always be protected to
 * prevent direct construction/destruction calls with the `new`/`delete`
 * operator.
 */
protected:
    /**
     * @brief Constructor for DatabaseController.
     *
     * Opens a connection to a SQLite database file. If the connection fails, it terminates the program.
     *
     */
    explicit DatabaseController() : db(nullptr), zErrMsg(nullptr) {
        int rc = sqlite3_open(FILENAME, &db);
        if (rc) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            exit(0);
        } else {
            std::cout << "Opened database successfully" << std::endl;
        }

        initializeDatabase(); // Initializes the database if required (creates it and adds tables)
    }

    /**
     * @brief Destructor for DatabaseController.
     *
     * Closes the connection to the SQLite database.
     */
    ~DatabaseController() {
        sqlite3_close(db); // TODO: This might need to be called else where (or add a method added to close it)
    }

public:
    static DatabaseController *getInstance();

    // Member functions
    void createTable();

    bool sqlOperation(const std::string &sql);


    // Using prepared statements for efficiency, easier replacements and security (prevents SQL injection):
    // https://stackoverflow.com/questions/61794729/how-does-prepared-statements-in-sqlite-c-work'
    std::vector<std::vector<std::string>> selectData(const std::string &sql);


    std::vector<std::string> getTables();

    static bool tableIsEmpty(const std::vector<std::vector<std::string>> &tableData);

    void initializeDatabase();

    // Prevent copying or moving the database object.
    DatabaseController(const DatabaseController &) = delete;

    DatabaseController &operator=(const DatabaseController &) = delete;

    DatabaseController(DatabaseController &&) = delete;

    DatabaseController &operator=(DatabaseController &&) = delete;
};

#endif // DATABASECONTROLLER_H
