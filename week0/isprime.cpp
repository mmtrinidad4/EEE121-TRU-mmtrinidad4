#include <iostream>
#include <limits>

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
        std::cout << "INPUT AN INTEGER : ";
        if (!(std::cin >> inputNumber)) {
            std::cout << std::endl;
            std::cout << "Invalid input. Please input an integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            invalidInput = true;
        } else {
            std::cout << std::endl;
            if (isPrime(inputNumber)) {
                std::cout << inputNumber << " IS A PRIME NUMBER" << std::endl;
            } else {
                std::cout << inputNumber << " IS NOT A PRIME NUMBER" << std::endl;
            }
        }

        if (!invalidInput) {
            std::cout << std::endl;
            std::cout << "Continue? Y/N. ";
            std::cin >> choice;
            if (choice != 'N' && choice != 'n' && choice != 'Y' && choice != 'y') {
                std::cout << "Invalid input. Please input Y or N." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                invalidInput = true;
            }
        }
        std::cout << std::endl;
    } while (!invalidInput && (choice == 'Y' || choice == 'y'));

    return 0;
}
