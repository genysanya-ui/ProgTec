#pragma once
#include <iostream>
#include <fstream>
#include <cstring>

class Base {
    public:
        virtual ~Base() {std::cout << "Base destructor called" << std::endl;}
        virtual Base* clone() const = 0;

        virtual void print(std::ostream& os) const = 0;
        virtual void save(std::ofstream& ofs) const = 0;
        virtual void load(std::ifstream& ifs) = 0;

        virtual const char* getName() const = 0;
        virtual const char* getType() const = 0;

        friend std::ostream& operator<<(std::ostream& os, const Base& obj) {
            obj.print(os);
            return os;
        }
        
        virtual bool equals(const Base& other) const = 0;
};