#include "ClipboardEntry.h"

std::string ClipboardEntry::getClipboardEntryID() const {
    return clipboardEntryID;
}

void ClipboardEntry::setClipboardEntryID(const std::string& value) {
    clipboardEntryID = value;
}

std::string ClipboardEntry::getDeviceID() const {
    return deviceID;
}

void ClipboardEntry::setDeviceID(const std::string& value) {
    deviceID = value;
}

std::string ClipboardEntry::getContent() const {
    return content;
}

void ClipboardEntry::setContent(const std::string& value) {
    content = value;
}

std::string ClipboardEntry::getContentPath() const {
    return contentPath;
}

void ClipboardEntry::setContentPath(const std::string& value) {
    contentPath = value;
}

std::string ClipboardEntry::getTimeAdded() const {
    return timeAdded;
}

void ClipboardEntry::setTimeAdded(const std::string& value) {
    timeAdded = value;
}

std::string ClipboardEntry::getUserTag() const {
    return userTag;
}

void ClipboardEntry::setUserTag(const std::string& value) {
    userTag = value;
}

