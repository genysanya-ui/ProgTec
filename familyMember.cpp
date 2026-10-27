#include "FamilyMember.h"
#include "exception.h"
#include <cstring>
#include <stdexcept>

void familyMember::copyStr(char*& dst, const char* src) {
    freeStr(dst);
    if (!src) { dst = nullptr; return; }
    dst = new char[std::strlen(src) + 1];
    std::strcpy(dst, src);
}
void familyMember::freeStr(char*& s) { delete[] s; s = nullptr; }

familyMember::familyMember()
    : name(nullptr), birthDate(nullptr), deathDate(nullptr), age(0),
      fatherName(nullptr), motherName(nullptr),
      spouseName(nullptr), marriageDate(nullptr), childrenList(nullptr) {
    std::cout << "[FamilyMember] default constructor\n";
    copyStr(name, "");
    copyStr(birthDate, "");
    copyStr(deathDate, "");
    copyStr(fatherName, "");
    copyStr(motherName, "");
    copyStr(spouseName, "");
    copyStr(marriageDate, "");
    copyStr(childrenList, "");
}

familyMember::familyMember(const char* n, const char* b, const char* d, int a,
                           const char* fa, const char* mo,
                           const char* sp, const char* md,
                           const char* ch)
    : name(nullptr), birthDate(nullptr), deathDate(nullptr), age(a),
      fatherName(nullptr), motherName(nullptr),
      spouseName(nullptr), marriageDate(nullptr), childrenList(nullptr) {
    std::cout << "[FamilyMember] parameterized constructor\n";
    if (a < 0) throw std::invalid_argument("Age cannot be negative");
    copyStr(name, n); copyStr(birthDate, b); copyStr(deathDate, d);
    copyStr(fatherName, fa); copyStr(motherName, mo);
    copyStr(spouseName, sp); copyStr(marriageDate, md);
    copyStr(childrenList, ch);
}

familyMember::familyMember(const familyMember& o)
    : name(nullptr), birthDate(nullptr), deathDate(nullptr), age(o.age),
      fatherName(nullptr), motherName(nullptr),
      spouseName(nullptr), marriageDate(nullptr), childrenList(nullptr) {
    std::cout << "[FamilyMember] copy constructor\n";
    copyStr(name, o.name); copyStr(birthDate, o.birthDate); copyStr(deathDate, o.deathDate);
    copyStr(fatherName, o.fatherName); copyStr(motherName, o.motherName);
    copyStr(spouseName, o.spouseName); copyStr(marriageDate, o.marriageDate);
    copyStr(childrenList, o.childrenList);
}

familyMember& familyMember::operator=(const familyMember& o) {
    std::cout << "[FamilyMember] operator=\n";
    if (this == &o) return *this;
    copyStr(name, o.name); copyStr(birthDate, o.birthDate); copyStr(deathDate, o.deathDate);
    age = o.age;
    copyStr(fatherName, o.fatherName); copyStr(motherName, o.motherName);
    copyStr(spouseName, o.spouseName); copyStr(marriageDate, o.marriageDate);
    copyStr(childrenList, o.childrenList);
    return *this;
}

familyMember::~familyMember() {
    std::cout << "[FamilyMember] destructor: " << (name ? name : "(null)") << "\n";
    freeStr(name); freeStr(birthDate); freeStr(deathDate);
    freeStr(fatherName); freeStr(motherName);
    freeStr(spouseName); freeStr(marriageDate); freeStr(childrenList);
}

void familyMember::print(std::ostream& os) const {
    os << "Name: " << (name ? name : "-") << "\n"
       << "Birth: " << (birthDate ? birthDate : "-") << "\n"
       << "Death: " << (deathDate && *deathDate ? deathDate : "alive") << "\n"
       << "Age: " << age << "\n"
       << "Father: " << (fatherName ? fatherName : "-") << "\n"
       << "Mother: " << (motherName ? motherName : "-") << "\n"
       << "Spouse: " << (spouseName ? spouseName : "-") << "\n"
       << "Marriage date: " << (marriageDate ? marriageDate : "-") << "\n"
       << "Children: " << (childrenList ? childrenList : "-") << "\n";
}

void familyMember::save(std::ofstream& ofs) const {
    ofs << (name ? name : "") << '\n'
        << (birthDate ? birthDate : "") << '\n'
        << (deathDate ? deathDate : "") << '\n'
        << age << '\n'
        << (fatherName ? fatherName : "") << '\n'
        << (motherName ? motherName : "") << '\n'
        << (spouseName ? spouseName : "") << '\n'
        << (marriageDate ? marriageDate : "") << '\n'
        << (childrenList ? childrenList : "") << '\n';
}

void familyMember::load(std::ifstream& ifs) {
    char buf[512];
    ifs.getline(buf, sizeof(buf)); copyStr(name, buf);
    ifs.getline(buf, sizeof(buf)); copyStr(birthDate, buf);
    ifs.getline(buf, sizeof(buf)); copyStr(deathDate, buf);
    ifs >> age;
    if (ifs.fail()) throw FileException("Invalid age in file");
    ifs.ignore();
    ifs.getline(buf, sizeof(buf)); copyStr(fatherName, buf);
    ifs.getline(buf, sizeof(buf)); copyStr(motherName, buf);
    ifs.getline(buf, sizeof(buf)); copyStr(spouseName, buf);
    ifs.getline(buf, sizeof(buf)); copyStr(marriageDate, buf);
    ifs.getline(buf, sizeof(buf)); copyStr(childrenList, buf);
}

bool familyMember::operator==(const familyMember& o) const {
    auto eq = [](const char* a, const char* b) {
        if (!a || !b) return a == b;
        return std::strcmp(a, b) == 0;
    };
    return eq(name, o.name);
}

bool familyMember::equals(const Base& other) const {
    const familyMember* p = dynamic_cast<const familyMember*>(&other);
    if (!p) return false;
    auto eq = [](const char* a, const char* b) {
        if (!a || !b) return a == b;
        return std::strcmp(a, b) == 0;
    };
    return eq(name, p->name) && eq(birthDate, p->birthDate) &&
           eq(deathDate, p->deathDate) && age == p->age &&
           eq(fatherName, p->fatherName) && eq(motherName, p->motherName) &&
           eq(spouseName, p->spouseName) && eq(marriageDate, p->marriageDate) &&
           eq(childrenList, p->childrenList);
}