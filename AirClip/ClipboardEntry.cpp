#include "ClipboardEntry.h"


std::string ClipboardEntry::getContent() const {
    return content;
}

std::string ClipboardEntry::getContentPath() const {
    return contentPath;
}

std::string ClipboardEntry::getType() const {
    switch (type) {
        case Type::Text: return "text";
        case Type::Image: return "image";
        case Type::File: return "file";
        default: return "Unknown";
    }
}
