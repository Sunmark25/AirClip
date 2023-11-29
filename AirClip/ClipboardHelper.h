#ifndef CLIPBOARDHELPER_H
#define CLIPBOARDHELPER_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "ClipboardEntry.h"
#include "DatabaseController.h"
#include "User.h"


class ClipboardHelper {
private:
    // Static Member Variables
    static std::string buffer; ///< Static buffer to hold the latest SQL statement.

    static const std::string escape(const std::string &input);

    static DatabaseController *dbc; ///< Static pointer to DatabaseController singleton instance.


//    static DatabaseController *dbc; // Store a reference to the database controller singleton


public:

    // SQL Generation Methods
    static const std::string generateCurrentTime();
    static const std::string generateUserInsertSQL(const std::string &username, const std::string &password);
    static const std::string generateUserDeleteSQL(const std::string &username);
    static const std::string generateUserSelectSQL(const std::string &userID);
    static const std::string generateUserUpdateSQL(const std::string &userID, const std::string &username = "", const std::string &password = "");
    static const std::string generateClipboardEntrySearchSQL(const std::string &searchContent);
    static const std::string generateClipboardEntryInsertSQL( const std::string timeAdded, const std::string deviceID, const std::string content, const std::string contentPath = "", const std::string userTag = "");
    static const std::string generateClipboardEntryDeleteSQL(const std::string &clipboardEntryID);
    static const std::string generateClipboardEntrySelectSQL(const std::string &clipboardEntryID);
    static const std::string generateClipboardEntryUpdateSQL(const std::string &clipboardEntryID, const std::string &timeAdded, const std::string &deviceID = "", const std::string &userTag = "", const std::string &content = "", const std::string &contentPath = "");// Enum Conversion Method

    // Enum Conversion Method
    static const std::string generateDeviceInsertSQL(const std::string &deviceName, const std::string &userID);
    static const std::string generateDeviceSelectSQL(const std::string &deviceID);

    static const std::string
    generateDeviceUpdateSQL(const std::string &deviceID, const std::string &deviceName = "", const std::string &userID = "");

    static const std::string generateDeviceDeleteSQL(const std::string &deviceID);


    static ClipboardEntry *getLatestClipboardEntry();

    static std::string findClipboardEntry(const std::string &deviceID, const std::string &content);


    static std::string insertClipboardEntry(std::string timeAdded, std::string deviceID, std::string content, std::string contentPath = "",
                         std::string userTag = "");

    static std::vector<ClipboardEntry *> searchClipboardEntry(const std::string &content);

    static ClipboardEntry *getLatestClipboardEntry(std::string deviceID);

    static ClipboardEntry *getClipboardEntry(const std::string &userId);

    static std::vector<ClipboardEntry*> getClipboardEntries(const std::string &userId);

    };



#endif // CLIPBOARDHELPER_H

