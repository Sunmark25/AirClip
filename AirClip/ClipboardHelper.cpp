#include "ClipboardHelper.h"

//TODO: Retrieve Information Fom ClipboardEntry

//bool ClipboardHelper::saveClipboardEntry(const std::string &userId, const ClipboardEntry &entry) {
//}
//
//ClipboardEntry ClipboardHelper::getClipboardEntry(const std::string &userId, int entryId) {
//}
//
//bool ClipboardHelper::removeClipboardEntry(const std::string &userId, int entryId) {
//}
//
//std::vector<ClipboardEntry> ClipboardHelper::getClipboardHistory(const std::string &userId) {
//
//}
//
//std::vector<ClipboardEntry>
//
//ClipboardHelper::searchClipboardHistory(const std::string &userId, const std::string &query) {
//
//}

const char* ClipboardHelper::generateInsertSQL(const std::string& userName, const std::string& userID, const std::string& deviceID, const std::string& deviceName) {
    std::stringstream sql;
    sql << "INSERT INTO AIRCLIP (userName, userID, deviceID, deviceName) VALUES ("
        << "'" << escape(userName) << "', "
        << "'" << escape(userID) << "', "
        << "'" << escape(deviceID) << "', "
        << "'" << escape(deviceName) << "');";
    buffer = sql.str();
    return buffer.c_str();
}

const char* ClipboardHelper::generateDeleteSQL(const std::string &userID) {
    std::stringstream sql;
    sql << "DELETE FROM AIRCLIP WHERE userID = '" << escape(userID) << "';";
    buffer = sql.str();
    return buffer.c_str();
}

const char* ClipboardHelper::generateSelectAllSQL() {
    buffer = "SELECT * FROM AIRCLIP;";
    return buffer.c_str();
}

const char* ClipboardHelper::generateUpdateSQL(const std::string &userID, const std::string &newUserName,
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

const std::string ClipboardHelper::escape(const std::string &input) {
    std::string output;
    for (char c : input) {
        if (c == '\'') output += c; // Duplicate the single quote for escaping
        output += c;
    }
    return output;
}

