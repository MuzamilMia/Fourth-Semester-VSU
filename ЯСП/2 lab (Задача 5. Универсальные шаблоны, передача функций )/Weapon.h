//#ifndef WEAPON_H
//#define WEAPON_H
//
//#include <string>
//#include <iostream>
//
//const int SLOTS = 3;
//
//struct Caliber {
//    double diameter{};
//    enum class Unit { Millimeter, Inch } unit;
//    Caliber() = default;
//    std::string to_string() const;
//    bool operator==(const Caliber& other);
//    friend std::istream& operator>>(std::istream& is, Caliber& c);
//};
//
//enum class Type {
//    Pistol, Rifle, Shotgun, SubmachineGun, SniperRifle
//};
//
//bool read_type(std::istream& stream, Type& type);
//
//struct Weapon {
//    int slot{};
//    std::string name{};
//    Caliber caliber{};
//    int count_of_bullets{};
//    double ownership_skill{};
//    double learning_rate{};
//    Type type{};
//
//    Weapon() = default;
//    Weapon(int slot, std::string name, Caliber caliber, int count_of_bullets,
//        double ownership_skill, double learning_rate, Type type);
//    std::string get_type() const;
//    bool shot();
//    bool operator==(const Weapon& other);
//
//    friend std::istream& operator>>(std::istream& stream, Weapon& weapon);
//    friend std::ostream& operator<<(std::ostream& stream, const Weapon& weap);
//};
//
//#endif // WEAPON_H

#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <iostream>

const int SLOTS = 3;

struct Caliber {
    double diameter{};
    enum class Unit { Millimeter, Inch } unit;
    //Caliber() = default;
    std::string to_string() const;
    bool operator==(const Caliber& other);
    friend std::istream& operator>>(std::istream& is, Caliber& c);
};

enum class Type {
    Melee, Ranged, Explosive, Energy, Pistol
};

bool read_type(std::istream& stream, Type& type);

struct Weapon {
    int slot{};
    std::string name{};
    Caliber caliber{};
    int count_of_bullets{};
    double ownership_skill{};
    double learning_rate{};
    Type type{};

    Weapon() = default;
    Weapon(int slot, std::string name, Caliber caliber, int count_of_bullets,
        double ownership_skill, double learning_rate, Type type);
    std::string get_type() const;
    bool shot();
    bool operator==(const Weapon& other);
    bool operator!=(const Weapon& other);

    friend std::istream& operator>>(std::istream& stream, Weapon& weapon);
    friend std::ostream& operator<<(std::ostream& stream, const Weapon& weap);
};

#endif // WEAPON_H