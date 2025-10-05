#include <iostream>
#include <string>
#include <set>
#include "../util.h"

int main() {


    std::string rawWords = "Hello, world! This is a test.";

    std::set<std::string> words = parseStringToWords(rawWords);

    for (std::set<std::string>::iterator it = words.begin(); it != words.end(); it++) {
        std::cout << *it << std::endl;
    }

    return 0;
}