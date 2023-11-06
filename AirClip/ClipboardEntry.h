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
    std::string clipboardEntryID;
    std::string content;
    std::string contentPath;
    Type type;
    std::string userID;

public:
    ClipboardEntry(const std::string clipboardEntryID, const std::string &content,
                   const std::string &contentPath, Type type, const std::string &userID) {
        this->clipboardEntryID = clipboardEntryID;
        this->content = content;
        this->contentPath = contentPath;
        this->type = type;
        this->userID = userID;
    }

    std::string getClipboardEntryID() const;

    std::string getContent() const;

    std::string getContentPath() const;

    std::string getType() const;

    std::string getUserID() const;

    void setClipboardEntryID(const std::string& id);

    void setContent(const std::string& newContent);

    void setContentPath(const std::string& newPath);

    void setType(Type newType);

    void setUserID(const std::string& newUserID);
};

#endif // CLIPBOARDENTRY_H
