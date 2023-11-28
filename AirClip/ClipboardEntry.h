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
    std::string clipboardEntryID;
    std::string timeAdded;
    std::string deviceID;
    std::string userTag;
    std::string content;
    std::string contentPath;

public:
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
    std::string getClipboardEntryID() const;
    std::string getDeviceID() const;
    std::string getContent() const;
    std::string getContentPath() const;
    std::string getTimeAdded() const;
    std::string getUserTag() const;

    // Setters
    void setClipboardEntryID(const std::string& value);
    void setDeviceID(const std::string& value);
    void setContent(const std::string& value);
    void setContentPath(const std::string& value);
    void setTimeAdded(const std::string& value);
    void setUserTag(const std::string& value);
};

#endif // CLIPBOARDENTRY_H
