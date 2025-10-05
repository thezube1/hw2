#include "clothing.h"
#include "util.h"

Clothing::Clothing(std::string name, std::string size, std::string brand, double price, int qty) : Product("clothing", name, price, qty), size_(size), brand_(brand) {
}

Clothing::~Clothing() {
}

std::set<std::string> Clothing::keywords() const {
    std::set<std::string> keys = parseStringToWords(name_);
    std::set<std::string> brandWords = parseStringToWords(brand_);
    keys.insert(convToLower(size_));
    keys.insert(brandWords.begin(), brandWords.end());
    return keys;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const {
    return std::find(searchTerms.begin(), searchTerms.end(), size_) != searchTerms.end() || std::find(searchTerms.begin(), searchTerms.end(), brand_) != searchTerms.end();
}

std::string Clothing::displayString() const {
    return name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Clothing::dump(std::ostream& os) const {
    os << "clothing" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
}