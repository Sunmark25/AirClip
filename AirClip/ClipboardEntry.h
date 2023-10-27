#ifndef CLIPBOARDENTRY_H
#define CLIPBOARDENTRY_H

#include <string>

class ClipboardEntry {
private:
    std::string content;
    std::string contentPath;
    std::string type;

public:
    ClipboardEntry(const std::string &content, const std::string &contentPath, const std::string &type) {

    }

    // Getter method to retrieve content
    [[nodiscard]] std::string getContent() const;

    // Getter method to retrieve content path
    [[nodiscard]] std::string getContentPath() const;

    // Getter method to retrieve type
    [[nodiscard]] std::string getType() const;
};

#endif // CLIPBOARDENTRY_H
