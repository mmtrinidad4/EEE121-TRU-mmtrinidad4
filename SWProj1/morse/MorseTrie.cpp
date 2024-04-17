#include "MorseTrie.h"
#include <iostream>

MorseTrie::MorseTrie() {
    root = new TrieNode();
    // MAPPINGS
    
    // CAPS
    char_to_morse['A'] = ".-";
    char_to_morse['B'] = "-...";
    char_to_morse['C'] = "-.-.";
    char_to_morse['D'] = "-..";
    char_to_morse['E'] = ".";
    char_to_morse['F'] = "..-.";
    char_to_morse['G'] = "--.";
    char_to_morse['H'] = "....";
    char_to_morse['I'] = "..";
    char_to_morse['J'] = ".---";
    char_to_morse['K'] = "-.-";
    char_to_morse['L'] = ".-..";
    char_to_morse['M'] = "--";
    char_to_morse['N'] = "-.";
    char_to_morse['O'] = "---";
    char_to_morse['P'] = ".--.";
    char_to_morse['Q'] = "--.-";
    char_to_morse['R'] = ".-.";
    char_to_morse['S'] = "...";
    char_to_morse['T'] = "-";
    char_to_morse['U'] = "..-";
    char_to_morse['V'] = "...-";
    char_to_morse['W'] = ".--";
    char_to_morse['X'] = "-..-";
    char_to_morse['Y'] = "-.--";
    char_to_morse['Z'] = "--..";
    
    // DIGITS
    char_to_morse['0'] = "-----";
    char_to_morse['1'] = ".----";
    char_to_morse['2'] = "..---";
    char_to_morse['3'] = "...--";
    char_to_morse['4'] = "....-";
    char_to_morse['5'] = ".....";
    char_to_morse['6'] = "-....";
    char_to_morse['7'] = "--...";
    char_to_morse['8'] = "---..";
    char_to_morse['9'] = "----.";
    
    // Special characters
    char_to_morse[' '] = "/";

    // INIT
    // Reverse mappings
    for (auto& pair : char_to_morse) {
        morse_to_char[pair.second] = pair.first;
    }
}

bool MorseTrie::encode(std::string word) {
    for (char& c : word) {
        if (char_to_morse.find(toupper(c)) == char_to_morse.end()) {
            std::cout << c << '\n';
            return false;
        }
        std::cout << char_to_morse[toupper(c)] << ' ';
    }
    std::cout << '\n';
    return true;
}

bool MorseTrie::decode(std::string morse) {
    std::string current_word;
    for (int i = 0; i < morse.length(); ++i) {
        char c = morse[i];
        if (c == ' ' || c == '/') {
            if (!current_word.empty()) {
                std::cout << morse_to_char[current_word];
                current_word.clear();
            }
            if (c == '/') { // treat '/' as space
                std::cout << ' ';
            }
        } else if (c == '.' || c == '-') {
            current_word += c;
        } else {
            std::cout << '\n';
            return false;
        }
    }
    if (!current_word.empty()) {
        std::cout << morse_to_char[current_word];
    }
    std::cout << '\n';
    return true;
}
