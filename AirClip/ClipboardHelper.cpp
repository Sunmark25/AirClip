#include "ClipboardHelper.h"
#include "DatabaseController.h"


//TODO: Retrieve Information For ClipboardEntry
//TODO: Generate Default Value For SQL

std::string ClipboardHelper::buffer;  // Initialize the static member variable (fixes build linker error)

DatabaseController* ClipboardHelper::dbc = DatabaseController::getInstance("");


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



// Generate Current Time in ISO8601 Format
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


const std::string ClipboardHelper::escape(const std::string &input) {
    std::string output;
    for (char c : input) {
        if (c == '\'') output += c; // Duplicate the single quote for escaping
        output += c;
    }
    return output;
}
