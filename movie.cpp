#include "movie.h"
#include "util.h"

Movie::Movie(std::string name, std::string genre, std::string rating, double price, int qty) : Product("movie", name, price, qty), genre_(genre), rating_(rating) {
}

Movie::~Movie() {
}

std::set<std::string> Movie::keywords() const {
    std::set<std::string> keys = parseStringToWords(name_);
    keys.insert(convToLower(genre_));
    keys.insert(convToLower(rating_));
    return keys;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const {
    return std::find(searchTerms.begin(), searchTerms.end(), genre_) != searchTerms.end() || std::find(searchTerms.begin(), searchTerms.end(), rating_) != searchTerms.end();
}

std::string Movie::displayString() const {
    return name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Movie::dump(std::ostream& os) const {
    os << "movie" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}