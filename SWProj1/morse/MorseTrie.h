#ifndef MORSETRIE_H
#define MORSETRIE_H

#include <unordered_map>
#include <string>

// morse node
struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool is_end_of_word;
};

// morse trie
class MorseTrie {

private:
    TrieNode* root;
    std::unordered_map<char, std::string> char_to_morse;
    std::unordered_map<std::string, char> morse_to_char;

public:
    MorseTrie(); // constructor
    bool encode(std::string word); // encoder - text to morse
    bool decode(std::string morse); // decoder - morse to text
};

#endif 
