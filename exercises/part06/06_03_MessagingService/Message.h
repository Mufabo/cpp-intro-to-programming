#pragma once

#include <string>

class Message {
public:
    Message(const std::string& sender, const std::string& content)
        : sender(sender), content(content) {
    }

    std::string getSender() const { return sender; }
    std::string getContent() const { return content; }

    bool operator==(const Message& other) const = default;

    std::string toString() const {
        return sender + ": " + content;
    }

private:
    std::string sender;
    std::string content;
};
