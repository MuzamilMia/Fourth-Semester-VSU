//#include "Weapon.h"
//#include <sstream>
//#include <iomanip>
//
//bool russian = false;
//
//std::string Caliber::to_string() const {
//    std::ostringstream oss;
//    oss << std::fixed << std::setprecision(2) << diameter;
//    oss << (unit == Unit::Inch ? (russian ? " дюйма" : " inches") : (russian ? " мм" : " mm"));
//    return oss.str();
//}
//
//bool Caliber::operator==(const Caliber& other) {
//    return diameter == other.diameter && unit == other.unit;
//}
//
//std::istream& operator>>(std::istream& is, Caliber& c) {
//    double value = 0.0;
//    if (!(is >> value)) {
//        throw std::runtime_error("Invalid caliber format");
//    }
//    c.diameter = value;
//    std::string unitStr;
//    if (is >> unitStr) {
//        if (unitStr == "mm" || unitStr == "мм") {
//            c.unit = Caliber::Unit::Millimeter;
//        }
//        else {
//            c.unit = Caliber::Unit::Inch;
//        }
//    }
//    return is;
//}
//
//bool read_type(std::istream& stream, Type& type) {
//    std::string str;
//    std::getline(stream, str);
//    if (str == "Pistol" || str == "Пистолет") {
//        type = Type::Pistol;
//        return true;
//    }
//    if (str == "Rifle" || str == "Винтовка") {
//        type = Type::Rifle;
//        return true;
//    }
//    if (str == "Shotgun" || str == "Дробовик") {
//        type = Type::Shotgun;
//        return true;
//    }
//    if (str == "SubmachineGun" || str == "Пистолет-пулемет") {
//        type = Type::SubmachineGun;
//        return true;
//    }
//    if (str == "SniperRifle" || str == "Снайперская винтовка") {
//        type = Type::SniperRifle;
//        return true;
//    }
//    return false;
//}
//
//Weapon::Weapon(int slot, std::string name, Caliber caliber, int count_of_bullets,
//    double ownership_skill, double learning_rate, Type type)
//    : slot(slot), name(name), caliber(caliber), count_of_bullets(count_of_bullets),
//    ownership_skill(ownership_skill), learning_rate(learning_rate), type(type) {
//}
//
//std::string Weapon::get_type() const {
//    if (russian) {
//        switch (type) {
//        case Type::Pistol: return "Пистолет";
//        case Type::Rifle: return "Винтовка";
//        case Type::Shotgun: return "Дробовик";
//        case Type::SubmachineGun: return "Пистолет-пулемет";
//        case Type::SniperRifle: return "Снайперская винтовка";
//        default: return "";
//        }
//    }
//    else {
//        switch (type) {
//        case Type::Pistol: return "Pistol";
//        case Type::Rifle: return "Rifle";
//        case Type::Shotgun: return "Shotgun";
//        case Type::SubmachineGun: return "SubmachineGun";
//        case Type::SniperRifle: return "SniperRifle";
//        default: return "";
//        }
//    }
//}
//
//
//bool Weapon::shot() {
//    if (!count_of_bullets) {
//        return false;
//    }
//    count_of_bullets--;
//    ownership_skill += learning_rate;
//    if (ownership_skill > 100) {
//        ownership_skill = 100;
//    }
//    return true;
//}
//
//bool Weapon::operator==(const Weapon& other) {
//    return slot == other.slot && name == other.name && caliber == other.caliber &&
//        count_of_bullets == other.count_of_bullets && ownership_skill == other.ownership_skill &&
//        learning_rate == other.learning_rate && type == other.type;
//}
//
//std::istream& operator>>(std::istream& stream, Weapon& weapon) {
//    Weapon tmp_weap;
//    int tmp_int;
//
//    stream >> tmp_int;
//    if (tmp_int == -1) {
//        throw std::runtime_error("End of input...");
//    }
//    if (tmp_int < 1 || tmp_int > SLOTS) {
//        throw std::invalid_argument("Invalid slot!");
//    }
//    tmp_weap.slot = tmp_int;
//    stream.ignore();
//
//    std::getline(stream, tmp_weap.name);
//
//    try {
//        stream >> tmp_weap.caliber;
//    }
//    catch (const std::runtime_error& ex) {
//        throw std::runtime_error("Error reading caliber");
//    }
//
//    stream >> tmp_int;
//    if (tmp_int < 0) {
//        throw std::invalid_argument("Invalid bullet count!");
//    }
//    tmp_weap.count_of_bullets = tmp_int;
//
//    double tmp_double;
//    stream >> tmp_double;
//    if (tmp_double < 0 || tmp_double > 100) {
//        throw std::invalid_argument("Invalid ownership skill!");
//    }
//    tmp_weap.ownership_skill = tmp_double;
//
//    stream >> tmp_double;
//    if (tmp_double < 0 || tmp_double > 100) {
//        throw std::invalid_argument("Invalid learning rate!");
//    }
//    tmp_weap.learning_rate = tmp_double;
//    stream.ignore();
//
//    if (!read_type(stream, tmp_weap.type)) {
//        throw std::invalid_argument("Invalid weapon type!");
//    }
//
//    weapon = tmp_weap;
//    return stream;
//}
//
//std::ostream& operator<<(std::ostream& stream, const Weapon& weap) {
//    stream << weap.slot << '\n';
//    stream << weap.name << '\n';
//    stream << weap.caliber.to_string() << '\n';
//    stream << weap.count_of_bullets << '\n';
//    stream << weap.ownership_skill << '\n';
//    stream << weap.learning_rate << '\n';
//    stream << weap.get_type() << '\n';
//    return stream;
//}

#include "Weapon.h"
#include <sstream>
#include <iomanip>

bool russian = false;

std::string Caliber::to_string() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << diameter;
    oss << (unit == Unit::Inch ? (russian ? " дюйма" : " inches") : (russian ? " мм" : " mm"));
    return oss.str();
}

bool Caliber::operator==(const Caliber& other) {
    return diameter == other.diameter && unit == other.unit;
}

std::istream& operator>>(std::istream& is, Caliber& c) {
    double value = 0.0;
    if (!(is >> value)) {
        throw std::runtime_error("Invalid caliber format");
    }
    c.diameter = value;
    std::string unitStr;
    if (is >> unitStr) {
        if (unitStr == "mm" || unitStr == "мм") {
            c.unit = Caliber::Unit::Millimeter;
        }
        else {
            c.unit = Caliber::Unit::Inch;
        }
    }
    return is;
}

bool read_type(std::istream& stream, Type& type) {
    std::string str;
    std::getline(stream, str);
    if (str == "Melee" || str == "Ближний бой") {
        type = Type::Melee;
        return true;
    }
    if (str == "Ranged" || str == "Дальний бой") {
        type = Type::Ranged;
        return true;
    }
    if (str == "Explosive" || str == "Взрывной") {
        type = Type::Explosive;
        return true;
    }
    if (str == "Energy" || str == "Энергетический") {
        type = Type::Energy;
        return true;
    }
    if (str == "Pistol" || str == "Пистолет") {
        type = Type::Pistol;
        return true;
    }
    return false;
}

Weapon::Weapon(int slot, std::string name, Caliber caliber, int count_of_bullets,
    double ownership_skill, double learning_rate, Type type)
    : slot(slot), name(name), caliber(caliber), count_of_bullets(count_of_bullets),
    ownership_skill(ownership_skill), learning_rate(learning_rate), type(type) {
}

std::string Weapon::get_type() const {
    if (russian) {
        switch (type) {
        case Type::Melee: return "Ближний бой";
        case Type::Ranged: return "Дальний бой";
        case Type::Explosive: return "Взрывной";
        case Type::Energy: return "Энергетический";
        case Type::Pistol: return "Пистолет";
        default: return "";
        }
    }
    else {
        switch (type) {
        case Type::Melee: return "Melee";
        case Type::Ranged: return "Ranged";
        case Type::Explosive: return "Explosive";
        case Type::Energy: return "Energy";
        case Type::Pistol: return "Pistol";
        default: return "";
        }
    }
}

bool Weapon::shot() {
    if (!count_of_bullets) {
        return false;
    }
    count_of_bullets--;
    ownership_skill += learning_rate;
    if (ownership_skill > 100) {
        ownership_skill = 100;
    }
    return true;
}

bool Weapon::operator==(const Weapon& other) {
    return slot == other.slot && name == other.name && caliber == other.caliber &&
        count_of_bullets == other.count_of_bullets && ownership_skill == other.ownership_skill &&
        learning_rate == other.learning_rate && type == other.type;
}

bool Weapon::operator!=(const Weapon& other)
{
    return !(slot == other.slot && name == other.name && caliber == other.caliber &&
        count_of_bullets == other.count_of_bullets && ownership_skill == other.ownership_skill &&
        learning_rate == other.learning_rate && type == other.type);
}

std::istream& operator>>(std::istream& stream, Weapon& weapon) {
    Weapon tmp_weap;
    int tmp_int;

    stream >> tmp_int;
    if (tmp_int == -1) {
        throw std::runtime_error("End of input...");
    }
    if (tmp_int < 1 || tmp_int > SLOTS) {
        throw std::invalid_argument("Invalid slot!");
    }
    tmp_weap.slot = tmp_int;
    stream.ignore();

    std::getline(stream, tmp_weap.name);

    try {
        stream >> tmp_weap.caliber;
    }
    catch (const std::runtime_error& ex) {
        throw std::runtime_error("Error reading caliber");
    }

    stream >> tmp_int;
    if (tmp_int < 0) {
        throw std::invalid_argument("Invalid bullet count!");
    }
    tmp_weap.count_of_bullets = tmp_int;

    double tmp_double;
    stream >> tmp_double;
    if (tmp_double < 0 || tmp_double > 100) {
        throw std::invalid_argument("Invalid ownership skill!");
    }
    tmp_weap.ownership_skill = tmp_double;

    stream >> tmp_double;
    if (tmp_double < 0 || tmp_double > 100) {
        throw std::invalid_argument("Invalid learning rate!");
    }
    tmp_weap.learning_rate = tmp_double;
    stream.ignore();

    if (!read_type(stream, tmp_weap.type)) {
        throw std::invalid_argument("Invalid weapon type!");
    }

    weapon = tmp_weap;
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Weapon& weap) {
    stream << weap.slot << '\n';
    stream << weap.name << '\n';
    stream << weap.caliber.to_string() << '\n';
    stream << weap.count_of_bullets << '\n';
    stream << weap.ownership_skill << '\n';
    stream << weap.learning_rate << '\n';
    stream << weap.get_type() << '\n';
    return stream;
}