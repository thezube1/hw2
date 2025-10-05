#include "product.h"
#include <set>
#include <vector>
#include <iostream>

class Movie : public Product {
public:
    Movie(std::string name, std::string genre, std::string rating, double price, int qty);
    ~Movie();
    std::set<std::string> keywords() const;
    bool isMatch(std::vector<std::string>& searchTerms) const;
    std::string displayString() const;  
    void dump(std::ostream& os) const;

private:
    std::string genre_;
    std::string rating_;
};
