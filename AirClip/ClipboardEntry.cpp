#include "ClipboardEntry.h"

std::string ClipboardEntry::getClipboardEntryID() const{
    return clipboardEntryID;
}

std::string ClipboardEntry::getContent() const {
    return content;
}

std::string ClipboardEntry::getContentPath() const {
    return contentPath;
}

Type ClipboardEntry::getType() const {
    return type;
}

std::string ClipboardEntry::getUserID() const {
    return userID;
}

void ClipboardEntry::setClipboardEntryID(const std::string& id) {
    clipboardEntryID = id;
}

void ClipboardEntry::setContent(const std::string& newContent) {
    content = newContent;
}

void ClipboardEntry::setContentPath(const std::string& newPath) {
    contentPath = newPath;
}

void ClipboardEntry::setType(Type newType) {
    type = newType;
}

void ClipboardEntry::setUserID(const std::string &newUserID) {
    userID = newUserID;
}