#include <iostream>
#include <limits>
#include <stdexcept>
#include "keeper.h"
#include "exception.h"
#include "familyMember.h"

static void inputLine(char* buf, int n) {
    std::cin.getline(buf, n);
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        buf[0] = '\0';
    }
}

static int inputInt(const char* prompt) {
    std::cout << prompt;
    int value;
    while (!(std::cin >> value)) {
        std::cout << "Invalid input. Please enter an integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

static Base* createMember() {
    char name[256], birth[32], death[32], father[256], mother[256],
         spouse[256], marriage[32], children[256];

    std::cout << "Enter name: ";                       
    inputLine(name, sizeof(name));
    
    std::cout << "Enter birth date: ";                 
    inputLine(birth, sizeof(birth));
    
    std::cout << "Enter death date: ";
    inputLine(death, sizeof(death));
    
    int age = inputInt("Enter age: ");
    
    std::cout << "Enter father's name: ";              
    inputLine(father, sizeof(father));
    
    std::cout << "Enter mother's name: ";              
    inputLine(mother, sizeof(mother));
    
    std::cout << "Enter spouse's name: ";              
    inputLine(spouse, sizeof(spouse));
    
    std::cout << "Enter marriage date: ";              
    inputLine(marriage, sizeof(marriage));
    
    std::cout << "Enter children list (via ';'): ";    
    inputLine(children, sizeof(children));

    return new familyMember(name, birth, death, age,
                            father, mother, spouse, marriage, children);
}

int main() {
    Keeper keeper;
    while (true) {
        std::cout << "\nMenu:\n"
                  << "1. Add member\n"
                  << "2. Remove\n"
                  << "3. Print all\n"
                  << "4. Save to file\n"
                  << "5. Load from file\n"
                  << "0. Exit\n";
        int choice = inputInt("Enter your choice: ");
        try {
            switch (choice) {
                case 1: keeper.add(createMember()); break;
                case 2: keeper.remove(inputInt("Enter index to remove: ")); break;
                case 3: keeper.printAll(std::cout); break;
                case 4: {
                    char filename[256];
                    std::cout << "Enter filename to save: ";
                    inputLine(filename, sizeof(filename));
                    keeper.saveToFile(filename);
                    break;
                }
                case 5: {
                    char filename[256];
                    std::cout << "Enter filename to load: ";
                    inputLine(filename, sizeof(filename));
                    keeper.loadFromFile(filename);
                    break;
                }
                case 0: return 0;
                default: std::cout << "Invalid choice. Please try again.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Exception: " << e.what() << "\n";
        }
    }
}