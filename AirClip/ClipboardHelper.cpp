#include "ClipboardHelper.h"
#include "DatabaseController.h"
#include <vector>


//TODO: Retrieve Information For ClipboardEntry
//TODO: Generate Default Value For SQL

std::string ClipboardHelper::buffer;  // Initialize the static member variable (fixes build linker error)

//void ClipboardHelper::saveClipboardEntry(const ClipboardEntry &entry)
//{
//    std::string sql_code = generateClipboardEntryInsertSQL(entry.getContent(), entry.getContentPath(), entry.getType(), entry.getUserID());
//    dbc->insertSQL(sql_code);
//}

ClipboardEntry* ClipboardHelper::getClipboardEntry(const std::string &userId, const int entryNum) {
    // Define the query to get all the clipboard entries for a user using their userID
    std::string query = "SELECT clipboardEntryID, userID, content, contentPath, contentType FROM CLIPBOARDENTRY WHERE userID ='" + userId + "';";

    // TODO: Make global
    DatabaseController *dbc = DatabaseController::getInstance("");

    // Look for the clipboard entries matching the userID
    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);

    // If clipboard entries were found (the table wasn't empty) then return the one the user requested
    if (!DatabaseController::tableIsEmpty(tableData)) {
        // Get the row based on the entryNum (0, 1, 2, 3)
        std::vector<std::string> row = tableData[entryNum];

        // Create a new clipboardEntry
        auto entry = new ClipboardEntry(row[0], row[2], row[3], stringToType(row[4]), row[1]);

        return entry;
    } else { // Otherwise, return an empty string
        std::cout << "No match for userID" << std::endl;

        return nullptr;
    }
}

//void ClipboardHelper::removeClipboardEntry(const std::string &clipBoardEntryId)
//{
//    std::string sql_code = generateClipboardEntryDeleteSQL(clipBoardEntryId);
//    dbc->deleteSQL(sql_code);
//}

//std::vector<ClipboardEntry> ClipboardHelper::getClipboardHistory(const std::string &userId)
//{
//    std::vector<ClipboardEntry> entry_history;
//    char* sql_code = generateClipboardEntrySelectAllSQL();
//    //TODO: a loop uses getClipboardEntry() from the database.
//    return NULL;
//}
//
//ClipboardHelper::searchClipboardHistory(const std::string &content)
//{
//    //TODO: search sql database stuff and return multiple values
//}

const std::string ClipboardHelper::getType(Type type) {
    switch (type) {
        case Type::Text: return "text";
        case Type::Image: return "image";
        case Type::File: return "file";
        default: return "Unknown";
    }
}

Type ClipboardHelper::stringToType(std::string typeString) {
    if (typeString == "text") {
        return Type::Text;
    } else if (typeString == "image") {
        return Type::Image;
    } else if (typeString == "file") {
        return Type::File;
    }
}

const std::string ClipboardHelper::generateAirClipInsertSQL(const std::string& userName, const std::string& userID, const std::string& deviceID, const std::string& deviceName) {
    std::stringstream sql;
    sql << "INSERT INTO AIRCLIP (userName, userID, deviceID, deviceName) VALUES ("
        << "'" << escape(userName) << "', "
        << "'" << escape(userID) << "', "
        << "'" << escape(deviceID) << "', "
        << "'" << escape(deviceName) << "');";
    buffer = sql.str();
    return buffer;
}

const std::string ClipboardHelper::generateAirClipDeleteSQL(const std::string &userID) {
    std::stringstream sql;
    sql << "DELETE FROM AIRCLIP WHERE userID = '" << escape(userID) << "';";
    buffer = sql.str();
    return buffer;
}

const std::string ClipboardHelper::generateAirClipSelectAllSQL() {
    buffer = "SELECT * FROM AIRCLIP;";
    return buffer;
}

const std::string ClipboardHelper::generateAirClipUpdateSQL(const std::string &userID, const std::string &newUserName,
                                               const std::string &newDeviceID, const std::string &newDeviceName) {
    std::stringstream sql;
    sql << "UPDATE AIRCLIP SET "
        << "userName = '" << escape(newUserName) << "', "
        << "deviceID = '" << escape(newDeviceID) << "', "
        << "deviceName = '" << escape(newDeviceName) << "' "
        << "WHERE userID = '" << escape(userID) << "';";
    buffer = sql.str();
    return buffer;
}

const std::string ClipboardHelper::generateClipboardEntryInsertSQL(
                                                             const std::string &content, const std::string &contentPath,
                                                             Type type, const std::string &userID) {
    std::stringstream sql;
    sql << "INSERT INTO CLIPBOARDENTRY (userID, content, contentPath, contentType) VALUES (";
    sql << "'" << escape(userID) << "', ";
    sql << "'" << escape(content) << "', ";
    sql << "'" << escape(contentPath) << "', ";
    sql << "'" << escape(getType(type)) << "');";

    buffer = sql.str();
    return buffer;
}

const std::string ClipboardHelper::generateClipboardEntryDeleteSQL(const std::string &clipboardEntryID) {
    std::stringstream sql;
    sql << "DELETE FROM CLIPBOARDENTRY WHERE clipboardEntryID = '" << escape(clipboardEntryID) << "';";
    buffer = sql.str();
    return buffer;
}

const std::string ClipboardHelper::generateClipboardEntryDeleteUserSQL(const std::string &userID) {
    std::stringstream sql;
    sql << "DELETE FROM CLIPBOARDENTRY WHERE userID = '" << escape(userID) << "';";
    buffer = sql.str();
    return buffer;
}

const std::string ClipboardHelper::generateClipboardEntrySelectAllSQL() {
    buffer = "SELECT * FROM CLIPBOARDENTRY;";
    return buffer;
}

const std::string ClipboardHelper::generateClipboardEntryUpdateSQL(const std::string &clipboardEntryID,
                                                             const std::string &newContent, const std::string &newContentPath,
                                                             Type newType, const std::string &newUserID) {
    std::stringstream sql;
    sql << "UPDATE CLIPBOARDENTRY SET "
        << "userID = '" << escape(newUserID) << "', "
        << "content = '" << escape(newContent) << "', "
        << "contentPath = '" << escape(newContentPath) << "', "
        << "contentType = '" << escape(getType(newType)) << "' "
        << "WHERE userID = '" << escape(clipboardEntryID) << "';";
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

