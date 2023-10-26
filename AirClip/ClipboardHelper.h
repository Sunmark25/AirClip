#ifndef CLIPBOARDHELPER_H
#define CLIPBOARDHELPER_H

#include <string>
#include <vector>
#include "ClipboardEntry.h" // Include the appropriate header for ClipboardEntry

class ClipboardHelper {
public:
    // Method to save a clipboard entry for a user
    static bool saveClipboardEntry(const std::string& userId, const ClipboardEntry& entry);

    // Method to get a clipboard entry for a user by entry ID
    static ClipboardEntry getClipboardEntry(const std::string& userId, int entryId);

    // Method to remove a clipboard entry for a user by entry ID
    static bool removeClipboardEntry(const std::string& userId, int entryId);

    // Method to get the clipboard history for a user
    static std::vector<ClipboardEntry> getClipboardHistory(const std::string& userId);

    // Method to search the clipboard history for a user by a query string
    static std::vector<ClipboardEntry> searchClipboardHistory(const std::string& userId, const std::string& query);
};

#endif // CLIPBOARDHELPER_H

