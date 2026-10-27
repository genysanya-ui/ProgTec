#include <iostream>
#include <limits>
#include "keeper.h"
#include "exception.h"
#include "parent.h"
#include "child.h"
#include "spouse.h"

static void inputLine(char* buf, int n) {
    std::cin.getline(buf, n);
};

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

static Base* createPerson(int type) {
    char name[256], birthDate[32], deathDate[32], fatherName[256], motherName[256], spouseName[256];
    std::cout << "Enter name: ";
    inputLine(name, sizeof(name));
    std::cout << "Enter birth date: ";
    inputLine(birthDate, sizeof(birthDate));
    std::cout << "Enter death date: ";
    inputLine(deathDate, sizeof(deathDate));

    int age = inputInt("Enter age: ");

    if(type == 1) { // Parent
        std::cout << "Enter father's name: ";
        inputLine(fatherName, sizeof(fatherName));
        std::cout << "Enter mother's name: ";
        inputLine(motherName, sizeof(motherName));
        std::cout << "Enter spouse's name: ";
        inputLine(spouseName, sizeof(spouseName));
        return new Parent(name, birthDate, deathDate, age, fatherName, motherName, spouseName);
    } else if(type == 2) { // Child
        std::cout << "Enter father's name: ";
        inputLine(fatherName, sizeof(fatherName));
        std::cout << "Enter mother's name: ";
        inputLine(motherName, sizeof(motherName));
        std::cout << "Enter spouse's name: ";
        inputLine(spouseName, sizeof(spouseName));
        return new Child(name, birthDate, deathDate, age, fatherName, motherName, spouseName);
    } else if(type == 3) { // Spouse
        std::cout << "Enter spouse's name: ";
        inputLine(spouseName, sizeof(spouseName));
        std::cout << "Enter marriage date: ";
        char marriageDate[32];
        inputLine(marriageDate, sizeof(marriageDate));
        std::cout << "Enter children list (separated by ';'): ";
        char childrenList[256];
        inputLine(childrenList, sizeof(childrenList));
        return new Spouse(name, birthDate, deathDate, age, spouseName, marriageDate, childrenList);
    }
    throw std::invalid_argument("Invalid type for person creation.");
}

int main() {
    Keeper keeper;
    int choice;

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Parent\n";
        std::cout << "2. Add Child\n";
        std::cout << "3. Add Spouse\n";
        std::cout << "4. Remove Person\n";
        std::cout << "5. Print All\n";
        std::cout << "6. Print by Type\n";
        std::cout << "7. Save to File\n";
        std::cout << "8. Load from File\n";
        std::cout << "9. Exit\n";
        choice = inputInt("Enter your choice: ");
        
        try {
            switch (choice) {
                case 1: keeper.add(createPerson(1)); break;
                case 2: keeper.add(createPerson(2)); break;
                case 3: keeper.add(createPerson(3)); break;
                case 4: {
                    int index = inputInt("Enter index to remove: ");
                    keeper.remove(index);
                    break;
                }
                case 5: keeper.printAll(std::cout); break;
                case 6: {
                    char type[32];
                    std::cout << "Enter type (Parent, Child, Spouse): ";
                    inputLine(type, sizeof(type));
                    keeper.printByType(std::cout, type[0]);
                    break;
                }
                case 7: {
                    char filename[256];
                    std::cout << "Enter filename to save: ";
                    inputLine(filename, sizeof(filename));
                    keeper.saveToFile(filename);
                    break;
                }
                case 8: {
                    char filename[256];
                    std::cout << "Enter filename to load: ";
                    inputLine(filename, sizeof(filename));
                    keeper.loadFromFile(filename);
                    break;
                }
                case 9: return 0;
                default: std::cout << "Invalid choice. Please try again." << std::endl;
            } 
        }catch (const EmptyKeeperException& e) {
                std::cout << "Exception: " << e.what() << "\n";
            }
}
}