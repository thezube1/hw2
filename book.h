#include <string>
#include "product.h"
#include <set>
#include <vector>
#include <iostream>


class Book : public Product {

public: 
    Book(std::string name, std::string author, std::string isbn, double price, int qty);
    ~Book();
    std::set<std::string> keywords() const;
    bool isMatch(std::vector<std::string>& searchTerms) const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

    

private:
    std::string author_;
    std::string isbn_;
};
