#include "book.h"
#include "util.h"

Book::Book(std::string name, std::string author, std::string isbn, double price, int qty) : Product("book", name, price, qty), author_(author), isbn_(isbn) {
}

Book::~Book() {
}

std::set<std::string> Book::keywords() const {
    std::set<std::string> keys = parseStringToWords(name_);
    std::set<std::string> authorWords = parseStringToWords(author_);
    keys.insert(authorWords.begin(), authorWords.end());
    // Keep ISBN as a single keyword to allow exact lookups with hyphens/digits
    keys.insert(convToLower(isbn_));
    return keys;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const {
    return std::find(searchTerms.begin(), searchTerms.end(), author_) != searchTerms.end() || std::find(searchTerms.begin(), searchTerms.end(), isbn_) != searchTerms.end();
}

std::string Book::displayString() const {
    return name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Book::dump(std::ostream& os) const {
    os << "book" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << std::endl;
}