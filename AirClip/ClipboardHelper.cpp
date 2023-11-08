#include "ClipboardHelper.h"
#include "DatabaseController.h"
#include <vector>


//TODO: Retrieve Information For ClipboardEntry
//TODO: Generate Default Value For SQL

//void ClipboardHelper::saveClipboardEntry(const ClipboardEntry &entry)
//{
//    std::string sql_code = generateClipboardEntryInsertSQL(entry.getContent(), entry.getContentPath(), entry.getType(), entry.getUserID());
//    dbc->insertSQL(sql_code);
//}

//ClipboardEntry ClipboardHelper::getClipboardEntry(const std::string &userId)
//{
//    char* sql_code = generateClipboardEntrySelectAllSQL();
//    //TODO: need a method that return entry from database
//    return NULL;
//}

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

std::string ClipboardHelper::buffer;  // Initialize the static member variable (fixes build linker error)

const std::string ClipboardHelper::getType(Type type) {
    switch (type) {
        case Type::Text: return "text";
        case Type::Image: return "image";
        case Type::File: return "file";
        default: return "Unknown";
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
    return buffer.c_str();
}

const std::string ClipboardHelper::generateAirClipDeleteSQL(const std::string &userID) {
    std::stringstream sql;
    sql << "DELETE FROM AIRCLIP WHERE userID = '" << escape(userID) << "';";
    buffer = sql.str();
    return buffer.c_str();
}

const std::string ClipboardHelper::generateAirClipSelectAllSQL() {
    buffer = "SELECT * FROM AIRCLIP;";
    return buffer.c_str();
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
    return buffer.c_str();
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
}

const std::string ClipboardHelper::generateClipboardEntryDeleteSQL(const std::string &clipboardEntryID) {
    std::stringstream sql;
    sql << "DELETE FROM CLIPBOARDENTRY WHERE clipboardEntryID = '" << escape(clipboardEntryID) << "';";
    buffer = sql.str();
    return buffer.c_str();
}

const std::string ClipboardHelper::generateClipboardEntryDeleteUserSQL(const std::string &userID) {
    std::stringstream sql;
    sql << "DELETE FROM CLIPBOARDENTRY WHERE userID = '" << escape(userID) << "';";
    buffer = sql.str();
    return buffer.c_str();
}

const std::string ClipboardHelper::generateClipboardEntrySelectAllSQL() {
    buffer = "SELECT * FROM CLIPBOARDENTRY;";
    return buffer.c_str();
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
    return buffer.c_str();
}


const std::string ClipboardHelper::escape(const std::string &input) {
    std::string output;
    for (char c : input) {
        if (c == '\'') output += c; // Duplicate the single quote for escaping
        output += c;
    }
    return output;
}

