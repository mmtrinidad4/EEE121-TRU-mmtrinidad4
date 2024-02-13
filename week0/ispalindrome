#include <iostream>
#include <string>

bool isPalindrome(std::string inputString) {
    for (int i = 0; i < inputString.length() / 2; i++) {
        if (inputString[i] != inputString[inputString.length() - i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    char choice;
    do {
        std::string inputString;
        std::cout << "INPUT A STRING: ";
        std::cin >> inputString;

        if (isPalindrome(inputString)) {
            std::cout << inputString << " IS A PALINDROME" << std::endl;
        } else {
            std::cout << inputString << " IS NOT A PALINDROME" << std::endl;
        }

        bool validChoice = false;
        do {
            std::cout << "Do you want to continue? (Y/N): ";
            std::cin >> choice;
            if (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n') {
                validChoice = true;
            } else {
                std::cerr << "Invalid choice. Please enter Y or N." << std::endl;
            }
        } while (!validChoice);

    } while (choice == 'Y' || choice == 'y');

    return 0;
}
