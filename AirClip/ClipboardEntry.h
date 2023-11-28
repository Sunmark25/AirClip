#ifndef CLIPBOARDENTRY_H
#define CLIPBOARDENTRY_H

#include <string>
#include <chrono>
#include <iomanip>

enum class Type{
    Text,
    Image,
    File
};


class ClipboardEntry {
private:
    std::string clipboardEntryID; ///< Unique identifier for the clipboard entry.
    std::string timeAdded;       ///< Timestamp of when the entry was added.
    std::string deviceID;         ///< Identifier of the device associated with the entry.
    std::string userTag;          ///< Optional tag or label set by the user for the entry.
    std::string content;          ///< The textual content of the clipboard entry.
    std::string contentPath;      ///< File path associated with the clipboard entry.

public:
    /**
    * @brief Constructor for ClipboardEntry.
    *
    * Initializes a new instance of the ClipboardEntry class with specified values for each attribute.
    *
    * @param clipboardEntryID The unique identifier for the clipboard entry.
    * @param timeAdded The timestamp indicating when the entry was added.
    * @param deviceID The identifier of the device associated with the entry.
    * @param userTag An optional tag or label set by the user for the entry.
    * @param content The textual content of the clipboard entry.
    * @param contentPath The file path associated with the clipboard entry, if applicable.
    */
    // put "" if this attribute does not exist for this ClipboardEntry
    ClipboardEntry(
            const std::string &clipboardEntryID,
            const std::string &timeAdded,
            const std::string &deviceID,
            const std::string &userTag,
            const std::string &content,
            const std::string &contentPath){
        this->clipboardEntryID = clipboardEntryID;
        this->timeAdded = timeAdded;
        this->deviceID = deviceID;
        this->userTag = userTag;
        this->content = content;
        this->contentPath = contentPath;
    }

    // Getters
    std::string getClipboardEntryID() const; ///< Returns the ID of the clipboard entry.
    std::string getDeviceID() const;         ///< Returns the ID of the device associated with the entry.
    std::string getContent() const;          ///< Returns the content of the clipboard entry.
    std::string getContentPath() const;      ///< Returns the file path associated with the entry, if applicable.
    std::string getTimeAdded() const;        ///< Returns the timestamp when the entry was added.
    std::string getUserTag() const;          ///< Returns the user tag or label associated with the entry.

    // Setters
    void setClipboardEntryID(const std::string& value); ///< Sets the ID of the clipboard entry.
    void setDeviceID(const std::string& value);         ///< Sets the ID of the device associated with the entry.
    void setContent(const std::string& value);          ///< Sets the content of the clipboard entry.
    void setContentPath(const std::string& value);      ///< Sets the file path associated with the entry.
    void setTimeAdded(const std::string& value);        ///< Sets the timestamp when the entry was added.
    void setUserTag(const std::string& value);          ///< Sets the user tag or label associated with the entry.
};;

#endif // CLIPBOARDENTRY_H
