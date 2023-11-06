#ifndef CLIPBOARDENTRY_H
#define CLIPBOARDENTRY_H

#include <string>
enum class Type{
    Text,
    Image,
    File
};

class ClipboardEntry {
private:
    std::string content;
    std::string contentPath;
    Type type;

public:
    ClipboardEntry(const std::string &content, const std::string &contentPath, Type type) {
        this->content = content;
        this->contentPath = contentPath;
        this->type = type;
    }

    // Getter method to retrieve content
    std::string getContent() const;

    // Getter method to retrieve content path
    std::string getContentPath() const;

    // Getter method to retrieve type
    std::string getType() const;
};

#endif // CLIPBOARDENTRY_H
