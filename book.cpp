#include "book.h"
#include "util.h"

Book::Book(std::string name, std::string author, std::string isbn, double price, int qty) : Product("book", name, price, qty), author_(author), isbn_(isbn) {
}

Book::~Book() {
}

std::set<std::string> Book::keywords() const {
    std::set<std::string> keywords = parseStringToWords(name_);
    keywords.insert(convToLower(author_));
    keywords.insert(convToLower(isbn_));
    return keywords;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const {
    return std::find(searchTerms.begin(), searchTerms.end(), author_) != searchTerms.end() || std::find(searchTerms.begin(), searchTerms.end(), isbn_) != searchTerms.end();
}

std::string Book::displayString() const {
    return name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Book::dump(std::ostream& os) const {
    os << "book" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << author_ << "\n" << isbn_ << std::endl;
}