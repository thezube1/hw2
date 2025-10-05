#include "product.h"
#include <set>
#include <vector>
#include <iostream>

class Clothing : public Product {
public:
    Clothing(std::string name, std::string size, std::string brand, double price, int qty);
    ~Clothing();
    std::set<std::string> keywords() const;
    bool isMatch(std::vector<std::string>& searchTerms) const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

private:
    std::string size_;
    std::string brand_;
};
