#ifndef CLIPBOARDHELPER_H
#define CLIPBOARDHELPER_H

#include <string>
#include <iostream>
#include <sstream>
#include "ClipboardEntry.h"
#include "DatabaseController.h"

class ClipboardHelper {
private:
    static std::string buffer; // Static buffer to hold the latest SQL statement

    static const std::string escape(const std::string &input);

    DatabaseController *dbc; // Store a reference to the database controller singleton


public:

    static const std::string getType(Type type);

    // Generate INSERT SQL statement
    static const std::string generateAirClipInsertSQL(const std::string& userName, const std::string& userID, const std::string& deviceID, const std::string& deviceName);

    // Generate DELETE SQL statement
    static const std::string generateAirClipDeleteSQL(const std::string& userID);

    // Generate SELECT ALL SQL statement
    static const std::string generateAirClipSelectAllSQL();

    // Generate UPDATE SQL statement
    static const std::string generateAirClipUpdateSQL(const std::string& userID, const std::string& newUserName, const std::string& newDeviceID, const std::string& newDeviceName);

    static const std::string generateClipboardEntryInsertSQL(const std::string& clipboardEntryID, const std::string& content,
                                                       const std::string& contentPath, Type type, const std::string& userID);

    const std::string generateClipboardEntryDeleteSQL(const std::string &clipboardEntryID);

    const std::string generateClipboardEntrySelectAllSQL();

    const std::string generateClipboardEntryUpdateSQL(const std::string &clipboardEntryID, const std::string &newContent,
                                                const std::string &newContentPath, Type newType,
                                                const std::string &newUserID);

    void saveClipboardEntry(const ClipboardEntry &entry);

    void removeClipboardEntry(const std::string &clipBoardEntryId);
};

#endif // CLIPBOARDHELPER_H

