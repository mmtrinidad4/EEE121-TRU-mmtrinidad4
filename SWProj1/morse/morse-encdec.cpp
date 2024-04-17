#include "MorseTrie.h"
#include <iostream>
using namespace std;

int main() {
    MorseTrie trie;

    std::string input;
    std::cout <<"";
    std::getline(std::cin, input);

    // used to determine whether morse or text
    if (input.find_first_of(".-") != std::string::npos) {
        if (trie.decode(input)) {
            std::cout << std::endl;
        } else {
            std::cout << std::endl;
        }
    } else {
        if (trie.encode(input)) {
            std::cout << std::endl;
        } else {
            std::cout << std::endl;
        }
    }

    return 0;
}
