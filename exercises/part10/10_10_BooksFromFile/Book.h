#pragma once

#include <format>
#include <string>

class Book {
public:
    Book(const std::string& name, int publishingYear, int pageCount, const std::string& author)
        : name(name), publishingYear(publishingYear), pageCount(pageCount), author(author) {
    }

    std::string getName() const { return name; }
    int getPublishingYear() const { return publishingYear; }
    int getPageCount() const { return pageCount; }
    std::string getAuthor() const { return author; }

    std::string toString() const {
        return std::format("{} ({}), {} pages, by {}", name, publishingYear, pageCount, author);
    }

private:
    std::string name;
    int publishingYear;
    int pageCount;
    std::string author;
};
