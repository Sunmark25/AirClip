#ifndef CLIPBOARDHELPER_H
#define CLIPBOARDHELPER_H

#include <string>
#include <iostream>
#include <sstream>
#include "ClipboardEntry.h"

class ClipboardHelper {
private:
    static std::string buffer; // Static buffer to hold the latest SQL statement

    static const std::string escape(const std::string &input);


public:
    static const std::string getType(Type type);

    // Generate INSERT SQL statement
    static const char* generateAirClipInsertSQL(const std::string& userName, const std::string& userID, const std::string& deviceID, const std::string& deviceName);

    // Generate DELETE SQL statement
    static const char* generateAirClipDeleteSQL(const std::string& userID);

    // Generate SELECT ALL SQL statement
    static const char* generateAirClipSelectAllSQL();

    // Generate UPDATE SQL statement
    static const char* generateAirClipUpdateSQL(const std::string& userID, const std::string& newUserName, const std::string& newDeviceID, const std::string& newDeviceName);

    static const char* generateClipboardEntryInsertSQL(const std::string& clipboardEntryID, const std::string& content,
                                                       const std::string& contentPath, Type type, const std::string& userID);

    const char *generateClipboardEntryDeleteSQL(const std::string &clipboardEntryID);

    const char *generateClipboardEntrySelectAllSQL();

    const char *generateClipboardEntryUpdateSQL(const std::string &clipboardEntryID, const std::string &newContent,
                                                const std::string &newContentPath, Type newType,
                                                const std::string &newUserID);
};

#endif // CLIPBOARDHELPER_H

