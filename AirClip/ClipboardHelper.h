#ifndef CLIPBOARDHELPER_H
#define CLIPBOARDHELPER_H

#include <string>
#include <iostream>
#include <sstream>

class ClipboardHelper {
private:
    static std::string buffer; // Static buffer to hold the latest SQL statement

    static const std::string escape(const std::string &input);


public:
    // Generate INSERT SQL statement
    static const char* generateInsertSQL(const std::string& userName, const std::string& userID, const std::string& deviceID, const std::string& deviceName);

    // Generate DELETE SQL statement
    static const char* generateDeleteSQL(const std::string& userID);

    // Generate SELECT ALL SQL statement
    static const char* generateSelectAllSQL();

    // Generate UPDATE SQL statement
    static const char* generateUpdateSQL(const std::string& userID, const std::string& newUserName, const std::string& newDeviceID, const std::string& newDeviceName);

};

#endif // CLIPBOARDHELPER_H

