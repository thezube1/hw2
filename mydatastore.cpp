#include "mydatastore.h"
#include <iostream>
#include <sstream>

MyDataStore::MyDataStore() {
}

MyDataStore::~MyDataStore() {
    for (Product* p : products_) {
        delete p;
    }
    for (std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        delete it->second;
    }
}

void MyDataStore::addProduct(Product* p) {
    if (p == nullptr) return;
    
    products_.push_back(p);
    buildKeywordIndex(p);
}

void MyDataStore::addUser(User* u) {
    if (u == nullptr) return;
    
    std::string username = convToLower(u->getName());
    users_[username] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::vector<Product*> results;
    
    if (terms.empty()) {
        lastSearchResults_ = results;
        return results;
    }
    
    // get the set of products for the first term
    std::string firstTerm = convToLower(terms[0]);
    std::set<Product*> currentSet;
    
    if (keywordIndex_.find(firstTerm) != keywordIndex_.end()) {
        currentSet = keywordIndex_[firstTerm];
    }
    
    // Get remaining terms from search type
    for (size_t i = 1; i < terms.size(); i++) {
        std::string term = convToLower(terms[i]);
        std::set<Product*> termSet;
        
        if (keywordIndex_.find(term) != keywordIndex_.end()) {
            termSet = keywordIndex_[term];
        }
        
        if (type == 0) {
            currentSet = setIntersection(currentSet, termSet);
        } else {
            currentSet = setUnion(currentSet, termSet);
        }
    }
    
    for (Product* p : currentSet) {
        results.push_back(p);
    }
    
    lastSearchResults_ = results;
    
    return results;
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "products" << std::endl;
    for (Product* p : products_) {
        p->dump(ofile);
    }
    
    ofile << "users" << std::endl;
    for (std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        it->second->dump(ofile);
    }
}

void MyDataStore::addToCart(const std::string& username, int hit_result_index) {
    std::string lowerUsername = convToLower(username);
    User* user = findUser(lowerUsername);
    
    if (user == nullptr) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    
    if (hit_result_index < 1 || hit_result_index > (int)lastSearchResults_.size()) {
        std::cout << "Invalid request" << std::endl;
        return;
    }
    
    // first in first out order
    Product* product = lastSearchResults_[hit_result_index - 1];
    carts_[lowerUsername].push(product);
}

void MyDataStore::viewCart(const std::string& username) {
    std::string lowerUsername = convToLower(username);
    User* user = findUser(lowerUsername);
    
    if (user == nullptr) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    
    if (carts_.find(lowerUsername) == carts_.end() || carts_[lowerUsername].empty()) {
        std::cout << "Cart is empty" << std::endl;
        return;
    }
    
    // display cart items
    std::queue<Product*> tempQueue = carts_[lowerUsername];
    int index = 1;
    
    while (!tempQueue.empty()) {
        Product* p = tempQueue.front();
        tempQueue.pop();
        
        std::cout << "Item " << index << ":" << std::endl;
        std::cout << p->displayString() << std::endl;
        index++;
    }
}

void MyDataStore::buyCart(const std::string& username) {
    std::string lowerUsername = convToLower(username);
    User* user = findUser(lowerUsername);
    
    if (user == nullptr) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    
    if (carts_.find(lowerUsername) == carts_.end()) {
        return;
    }
    
    std::queue<Product*> newCart;
    
    while (!carts_[lowerUsername].empty()) {
        Product* p = carts_[lowerUsername].front();
        carts_[lowerUsername].pop();
        
        // check if product is available and user has money
        if (p->getQty() > 0 && user->getBalance() >= p->getPrice()) {

            p->subtractQty(1);
            user->deductAmount(p->getPrice());
        } else {
            newCart.push(p);
        }
    }
    
    carts_[lowerUsername] = newCart;
}

void MyDataStore::buildKeywordIndex(Product* p) {
    if (p == nullptr) return;
    
    std::set<std::string> keywords = p->keywords();
    
    for (const std::string& keyword : keywords) {
        std::string lowerKeyword = convToLower(keyword);
        keywordIndex_[lowerKeyword].insert(p);
    }
}

std::set<std::string> MyDataStore::extractKeywords(const std::string& text) {
    return parseStringToWords(text);
}

User* MyDataStore::findUser(const std::string& username) {
    std::string lowerUsername = convToLower(username);
    std::map<std::string, User*>::iterator it = users_.find(lowerUsername);
    return (it != users_.end()) ? it->second : nullptr;
}
