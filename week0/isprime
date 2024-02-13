#include <iostream>

bool isPrime(int number) {
    if (number <= 1) {
        return false;
    }
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    char choice;
    bool invalidInput;
    do {
        invalidInput = false;
        int inputNumber;
        std::cout << "INPUT AN INTEGER: ";
        std::cin >> inputNumber;
        
        if (isPrime(inputNumber)) {
            std::cout << inputNumber << " IS A PRIME NUMBER" << std::endl;
        } else {
            std::cout << inputNumber << " IS NOT A PRIME NUMBER" << std::endl;
        }

        std::cout << "Do you want to continue? (Y/N): ";
        std::cin >> choice;
        if (choice != 'N' && choice != 'n' && choice != 'Y' && choice != 'y') {
            std::cerr << "Invalid input. Program terminated." << std::endl;
            return 1; // Exit the program with an error status
        }
    } while (choice != 'N' && choice != 'n');

    return 0;
}
