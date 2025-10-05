#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include <map>
#include <vector>
#include <queue>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    // get functions from DataStore
    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;

    // Cart operations
    void addToCart(const std::string& username, int hit_result_index);
    void viewCart(const std::string& username);
    void buyCart(const std::string& username);

private:
    // Storing products and users
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    
    std::map<std::string, std::set<Product*>> keywordIndex_;

    // user carts
    std::map<std::string, std::queue<Product*>> carts_;
    
    std::vector<Product*> lastSearchResults_;
    
    void buildKeywordIndex(Product* p);
    std::set<std::string> extractKeywords(const std::string& text);
    User* findUser(const std::string& username);
};

#endif
