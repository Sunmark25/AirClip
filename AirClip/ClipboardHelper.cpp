/**
 * @class ClipboardHelper
 * @brief A utility class for managing clipboard entries, users, and devices in a database.
 *
 * This class provides static methods for various operations related to clipboard entries,
 * including searching, inserting, and retrieving entries, as well as managing user data.
 * It also includes methods to generate SQL queries for these operations and to convert
 * string representations to specific enum types.
 */

#include "ClipboardHelper.h"
#include "DatabaseController.h"


//TODO: Retrieve Information For ClipboardEntry
//TODO: Generate Default Value For SQL

std::string ClipboardHelper::buffer;  // Initialize the static member variable (fixes build linker error)

DatabaseController* ClipboardHelper::dbc = DatabaseController::getInstance();


//ClipboardEntry* ClipboardHelper::getClipboardEntry(const std::string &userId, const int entryNum) {
//    std::string query = "SELECT ClipboardEntry.* FROM ClipboardEntry JOIN DEVICE "
//                        "ON ClipboardEntry.deviceID = Device.deviceID JOIN User"
//                        "ON Device.userID = User.userID"
//                        "WHERE User.userID = '" + userId + "';";
//
//
//    // Look for the clipboard entries matching the userID
//    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);
//
//    // If clipboard entries were found (the table wasn't empty) then return the one the user requested
//    if (!DatabaseController::tableIsEmpty(tableData)) {
//        // Get the row based on the entryNum (0, 1, 2, 3)
//        std::vector<std::string> row = tableData[entryNum];
//
//        // Create a new clipboardEntry
//        auto entry = new ClipboardEntry(row[0], row[1], row[2], row[3], row[4], row[5]);
//
//        return entry;
//    } else { // Otherwise, return an empty string
//        std::cout << "No match for userID" << std::endl;
//
//        return nullptr;
//    }
//}

/**
 * @brief Retrieves a list of clipboard entries associated with a specific user ID.
 *
 * This method queries the database for all clipboard entries linked to the provided user ID.
 * It joins the ClipboardEntry, Device, and User tables to filter entries based on the user's
 * device. If entries are found, they are instantiated as ClipboardEntry objects and added to a vector.
 *
 * @param userId The user ID for which clipboard entries are to be retrieved.
 * @return std::vector<ClipboardEntry*> A vector of pointers to ClipboardEntry objects.
 *         If no matching entries are found, the vector will be empty.
 *
 * @note The method logs a message to the console if no matching entries are found for the provided user ID.
 */
std::vector<ClipboardEntry*> ClipboardHelper::getClipboardEntries(const std::string &userId) {
    std::string query = "SELECT ClipboardEntry.* FROM ClipboardEntry JOIN DEVICE "
                        "ON ClipboardEntry.deviceID = Device.deviceID JOIN User "
                        "ON Device.userID = User.userID "
                        "WHERE User.userID = '" + userId + "';";

    // Look for all clipboard entries matching the userID
    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);
    std::vector<ClipboardEntry*> entries;

    // Check if the table is not empty
    if (!DatabaseController::tableIsEmpty(tableData)) {
        // Iterate over each row and create a new clipboardEntry
        for (const auto& row : tableData) {
            auto entry = new ClipboardEntry(row[0], row[1], row[2], row[3], row[4], row[5]);
            entries.push_back(entry);
        }
    } else {
        std::cout << "No match for userID" << std::endl;
    }

    return entries;
}


//ClipboardEntry* ClipboardHelper::searchClipboardEntry(const std::string &content, const int entryNum){
//    std::string query = generateClipboardEntrySearchSQL(content);
//
//    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);
//
//    if (!DatabaseController::tableIsEmpty(tableData)) {
//        // Get the row based on the entryNum (0, 1, 2, 3)
//        std::vector<std::string> row = tableData[entryNum];
//
//        // Create a new clipboardEntry
//        auto entry = new ClipboardEntry(row[0], row[1], row[2], row[3], row[4], row[5]);
//
//        return entry;
//    } else { // Otherwise, return an empty string
//        std::cout << "No match for this content" << std::endl;
//
//        return nullptr;
//    }
//}

/**
 * @brief Searches and retrieves clipboard entries that match the specified content.
 *
 * This method performs a database search for clipboard entries containing the given content.
 * It generates an SQL query using the `generateClipboardEntrySearchSQL` method and executes
 * it to find matching entries. Each found entry is instantiated as a ClipboardEntry object
 * and added to a vector. The search is performed using the LIKE operator in SQL, allowing for
 * partial matches with the specified content.
 *
 * @param content The string content to search for in clipboard entries.
 * @return std::vector<ClipboardEntry*> A vector of pointers to ClipboardEntry objects.
 *         If no entries match the search content, the vector will be empty.
 *
 * @note The method logs a message to the console if no entries matching the specified content are found.
 */
std::vector<ClipboardEntry*> ClipboardHelper::searchClipboardEntry(const std::string &content){
    std::string query = generateClipboardEntrySearchSQL(content);

    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);
    std::vector<ClipboardEntry*> entries;

    if (!DatabaseController::tableIsEmpty(tableData)) {
        // Iterate over each row and create a new clipboardEntry
        for (const auto& row : tableData) {
            auto entry = new ClipboardEntry(row[0], row[1], row[2], row[3], row[4], row[5]);
            entries.push_back(entry);
        }
    } else {
        std::cout << "No match for this content" << std::endl;
    }

    return entries;
}

/**
 * @brief Inserts a new clipboard entry into the database.
 *
 * This method constructs and executes an SQL query to insert a new clipboard entry into the database.
 * The insertion is based on the provided time added, device ID, content, content path, and user tag.
 * After the insertion, it attempts to retrieve the newly added clipboard entry by calling
 * `findClipboardEntry` using the device ID and content as search parameters.
 *
 * @param timeAdded The timestamp when the clipboard entry was added.
 * @param deviceID The ID of the device associated with the clipboard entry.
 * @param content The textual content of the clipboard entry.
 * @param contentPath The file path associated with the clipboard entry, if applicable.
 * @param userTag A tag or label associated with the clipboard entry.
 * @return std::string The ID of the newly added clipboard entry if insertion is successful; an empty string otherwise.
 *
 * @note The method logs a success message to the console upon successful insertion. If the insertion fails,
 *       it logs a message indicating the failure to add a new entry in the database.
 */
std::string ClipboardHelper::insertClipboardEntry(std::string timeAdded,
                                                  std::string deviceID,
                                                  std::string content,
                                                  std::string contentPath,
                                                  std::string userTag){

    std::string query = generateClipboardEntryInsertSQL(timeAdded, deviceID, content, contentPath, userTag);

    bool success = dbc->sqlOperation(query);

    if (success) {
        std::cout << "Success" << std::endl;
        return findClipboardEntry(deviceID, content);
    } else { // Otherwise, return an empty string
        std::cout << "Unable to add a new device in the database" << std::endl;
        return "";
    }
}

/**
 * @brief Finds the ID of a clipboard entry based on device ID and content.
 *
 * This method constructs and executes an SQL query to find the clipboard entry ID corresponding to
 * the specified device ID and content. If a matching entry is found, the entry ID is logged and returned.
 *
 * @param deviceID The ID of the device associated with the clipboard entry.
 * @param content The content of the clipboard entry.
 * @return std::string The ID of the found clipboard entry; returns an empty string if no match is found.
 *
 * @note Logs a message to the console indicating whether a matching entry was found or not.
 */
std::string ClipboardHelper::findClipboardEntry(const std::string &deviceID, const std::string &content){
    std::string query = "SELECT clipboardEntryID FROM ClipboardEntry WHERE deviceID = '" + deviceID + "' AND content = '" + content + "';";

    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);

    if (!DatabaseController::tableIsEmpty(tableData)) {
        std::string clipboardEntryID = tableData[0][0];

        std::cout << "Clipboard Entry ID: " << clipboardEntryID << std::endl;

        return deviceID;
    } else { // Otherwise, return an empty string
        std::cout << "No match for device id and content" << std::endl;

        return "";
    }
}


/**
 * @brief Retrieves the most recent clipboard entry for a given device ID.
 *
 * This method fetches the latest clipboard entry from the database for the specified device ID.
 * The clipboard entries are ordered by the time they were added, and the most recent one is returned.
 *
 * @param deviceID The ID of the device for which the latest clipboard entry is to be retrieved.
 * @return ClipboardEntry* Pointer to the most recent ClipboardEntry object; returns nullptr if no entry is found.
 *
 * @note Logs a message to the console if no matching entry is found for the specified device ID.
 */
ClipboardEntry* ClipboardHelper::getLatestClipboardEntry(std::string deviceID) {
    // Correct the order of clauses in the SQL query
    std::string query = "SELECT * FROM ClipboardEntry WHERE deviceID = '" + deviceID + "' ORDER BY timeAdded DESC LIMIT 1;";

    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);

    if (!DatabaseController::tableIsEmpty(tableData)) {
        // Get the first row (which is the latest entry)
        std::vector<std::string> row = tableData[0];

        // Create a new clipboardEntry
        auto entry = new ClipboardEntry(row[0], row[1], row[2], row[3], row[4], row[5]);

        return entry;
    } else {
        std::cout << "No match for this content" << std::endl;
        return nullptr;
    }
}

/**
 * @brief Retrieves the most recent clipboard entry from the database.
 *
 * This method fetches the latest clipboard entry from the database without filtering by device ID.
 * The clipboard entries are ordered by the time they were added, and the most recent one is returned.
 *
 * @return ClipboardEntry* Pointer to the most recent ClipboardEntry object; returns nullptr if no entry is found.
 *
 * @note Logs a message to the console if no clipboard entry is found.
 */
ClipboardEntry* ClipboardHelper::getLatestClipboardEntry (){
    std::string query = "SELECT * FROM ClipboardEntry ORDER BY timeAdded DESC LIMIT 1;";

    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);

    if (!DatabaseController::tableIsEmpty(tableData)) {
        // Get the row based on the entryNum (0, 1, 2, 3)
        std::vector<std::string> row = tableData[0];

        // Create a new clipboardEntry
        auto entry = new ClipboardEntry(row[0], row[1], row[2], row[3], row[4], row[5]);

        return entry;
    } else { // Otherwise, return an empty string
        std::cout << "No match for this content" << std::endl;

        return nullptr;
    }
}


/**
 * @brief Generates the current time in ISO8601 format.
 *
 * This method generates a timestamp of the current time, formatted according to the ISO8601 standard.
 * The format used is 'YYYY-MM-DD_HH:MM:SS'.
 *
 * @return std::string A string representing the current time in ISO8601 format.
 */
const std::string ClipboardHelper::generateCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);

    std::ostringstream stream;
    stream << std::put_time(std::localtime(&now_c), "%Y-%m-%d_%H:%M:%S");

    return stream.str();
}


const std::string ClipboardHelper::generateUserInsertSQL(const std::string &username, const std::string &password){
    std::stringstream sql;
    sql << "INSERT INTO User (username, password) VALUES ("
        << "'" << escape(username) << "', "
        << "'" << escape(password) << "');";
    buffer = sql.str();
    return buffer;
}


const std::string ClipboardHelper::generateUserDeleteSQL(const std::string &username){
    std::stringstream sql;
    sql << "DELETE FROM User WHERE username = '" << escape(username) << "';";
    buffer = sql.str();
    return buffer;
}


const std::string ClipboardHelper::generateUserSelectSQL(const std::string &userID){
    std::stringstream sql;
    sql << "SELECT * FROM User WHERE userID = '" << escape(userID) << "';";
    buffer = sql.str();
    return buffer;
}


const std::string ClipboardHelper::generateUserUpdateSQL(
        const std::string &userID,
        const std::string &username,
        const std::string &password
) {
    std::stringstream sql;
    sql << "UPDATE User SET ";

    // Conditionally append username
    if (!username.empty()) {
        sql << "username = '" << escape(username) << "'";
    }

    // Conditionally append password
    if (!password.empty()) {
        if (!username.empty()) {
            sql << ", "; // Add a comma only if username was also set
        }
        sql << "password = '" << escape(password) << "'";
    }

    sql << " WHERE userID = '" << escape(userID) << "';";

    buffer = sql.str();
    return buffer;
}

const std::string ClipboardHelper::generateClipboardEntrySearchSQL(const std::string &searchContent){
    std::stringstream sql;
    // Use the LIKE operator for pattern matching in SQLite
    sql << "SELECT * FROM ClipboardEntry WHERE content LIKE '%" << escape(searchContent) << "%';";
    buffer = sql.str();
    return buffer;
}

// use generateCurrentTime for timeAdded
const std::string ClipboardHelper::generateClipboardEntryInsertSQL(
        const std::string timeAdded,
        const std::string deviceID,
        const std::string content,
        const std::string contentPath,
        const std::string userTag
){
    std::stringstream sql;
    sql << "INSERT INTO ClipboardEntry (timeAdded, deviceID, userTag, content, contentPath) VALUES (";
    sql << "'" << escape(timeAdded) << "', ";
    sql << "'" << escape(deviceID) << "', ";
    sql << "'" << escape(userTag) << "', ";
    sql << "'" << escape(content) << "', ";
    sql << "'" << escape(contentPath) << "');";

    buffer = sql.str();
    return buffer;
}

const std::string ClipboardHelper::generateClipboardEntryDeleteSQL(const std::string &clipboardEntryID) {
    std::stringstream sql;
    sql << "DELETE FROM ClipboardEntry WHERE clipboardEntryID = '" << escape(clipboardEntryID) << "';";
    buffer = sql.str();
    return buffer;
}


const std::string ClipboardHelper::generateClipboardEntrySelectSQL(const std::string &clipboardEntryID){
    std::stringstream sql;
    sql << "SELECT * FROM ClipboardEntry WHERE clipboardEntryID = '" << escape(clipboardEntryID) << "';";
    buffer = sql.str();
    return buffer;
}

//TODO: Update 'ClipboardEntry.h' so objects know it's clipboardID
const std::string ClipboardHelper::generateClipboardEntryUpdateSQL(
        const std::string &clipboardEntryID,
        const std::string &timeAdded,
        const std::string &deviceID,
        const std::string &userTag,
        const std::string &content,
        const std::string &contentPath
) {
    std::stringstream sql;
    sql << "UPDATE ClipboardEntry SET ";

    // Always update timeAdded
    sql << "timeAdded = '" << escape(timeAdded) << "'";

    // Conditionally append other fields
    if (!deviceID.empty()) {
        sql << ", deviceID = '" << escape(deviceID) << "'";
    }
    if (!userTag.empty()) {
        sql << ", userTag = '" << escape(userTag) << "'";
    }
    if (!content.empty()) {
        sql << ", content = '" << escape(content) << "'";
    }
    if (!contentPath.empty()) {
        sql << ", contentPath = '" << escape(contentPath) << "'";
    }

    sql << " WHERE clipboardEntryID = '" << escape(clipboardEntryID) << "';";

    buffer = sql.str();
    return buffer;
}

const std::string ClipboardHelper::generateDeviceInsertSQL(
        const std::string &deviceName,
        const std::string &userID
        ){
    std::stringstream sql;
    sql << "INSERT INTO Device (deviceName, userID) VALUES ("
            << "'" << escape(deviceName) << "', "
            << "'" << escape(userID) << "');";

    buffer = sql.str();
    return buffer;
}

const std::string ClipboardHelper::generateDeviceSelectSQL(const std::string &deviceID){
    std::stringstream sql;
    sql << "SELECT * FROM Device WHERE deviceID = '" << escape(deviceID) << "';";
    buffer = sql.str();
    return buffer;
}

const std::string ClipboardHelper::generateDeviceUpdateSQL(
        const std::string &deviceID,
        const std::string &deviceName,
        const std::string &userID
        ){
    std::stringstream sql;
    sql << "UPDATE Device SET ";
    if (!deviceName.empty()) {
        sql << ", deviceName = '" << escape(deviceName) << "'";
    }
    if (!userID.empty()) {
        sql << ", userID = '" << escape(userID) << "'";
    }
    sql << " WHERE deviceID = '" << escape(deviceID) << "';";

    buffer = sql.str();
    return buffer;
}

const std::string ClipboardHelper::generateDeviceDeleteSQL(
        const std::string &deviceID
        ){
    std::stringstream sql;
    sql << "DELETE FROM Device WHERE deviceID = '" << escape(deviceID) << "';";
    buffer = sql.str();
    return buffer;
}

/**
 * @brief Escapes single quotes in a string for SQL queries.
 *
 * This method duplicates single quotes within the input string, which is a common method for escaping
 * single quotes in SQL queries. This is necessary to prevent SQL injection and syntax errors in queries.
 *
 * @param input The string to be escaped.
 * @return std::string The escaped string.
 */
const std::string ClipboardHelper::escape(const std::string &input) {
    std::string output;
    for (char c : input) {
        if (c == '\'') output += c; // Duplicate the single quote for escaping
        output += c;
    }
    return output;
}
