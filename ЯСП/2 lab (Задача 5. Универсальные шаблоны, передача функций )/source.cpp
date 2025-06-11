#include <Windows.h>
#include <fstream>
#include <iostream>
#include <limits>
#include "Weapon.h"
#include "Container.h"
#include "Player.h"

int check_file(std::ifstream& file) {
    int result = -1;
    if (file.is_open()) {
        if (file.peek() == EOF) result = 0;
        else result = 1;
    }
    return result;
}

int validation(const char* message, int left, int right) {
    int x;
    while (true) {
        if (std::cin >> x && x >= left && x <= right) {
            return x;
        }
        std::cout << message;
        std::cin.clear();
        std::cin.ignore();
    }
}

void show_template() {
    std::cout <<
        "---------------------My Item---------------------\n"
        "Slot: <int>\n"
        "Name: <std::string>\n"
        "Caliber <double inches/mm>\n"
        "Bullet count <int>\n"
        "Ownership skill <double>\n"
        "Learning rate per shot <double>\n"
        "Type: <Pistol, Energy, Ranged, Explosive, Melee, OR Пистолет, Дальний бой,Взрывной, Энергетический >\n"
        "---------------------My Item---------------------\n\n";
}

int Display_menu() {
    std::cout << "\n=== Arsenal Management System ===\n"
        "1. Add weapons from console\n"
        "2. Add weapons from file\n"
        "3. Clear Inventory\n"
        "4. Display Inventory (Console)\n"
        "5. Save Inventory to File\n"
        "6. Remove weapon\n"
        "7. Select by name range\n"
        "8. Select by type\n"
        "9. Replace weapon\n"
        "10.Pick up weapon (Player)\n"
        "11.Drop weapon from slot (Player)\n"
        "12.Shoot (Player)\n"
        "13.Show weapons in slots (Player)\n"
        "14. Exit\n"
        "========================================= \n";
    return validation("Enter valid menu option!\n", 1, 14);
}

void add_from_console(Container<Weapon>& container) {
    try {
        std::cout << "\nEnter data per template (enter -1 in Slot to stop)\n\n";
        show_template();
        try {
            std::cin >> container;
        }
        catch (const std::runtime_error& ex) {
            std::cout << "End of input...\n";
        }
        catch (const std::invalid_argument& ex) {
            std::cout << "Read error! " << ex.what() << '\n';
        }
    }
    catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }
}

void add_from_file(Container<Weapon>& container) 
{
    std::cin.ignore();
    std::cout << "\nEnter filename with extension: ";
    std::string filename;
    std::getline(std::cin, filename);
    std::ifstream file(filename);
    int check = check_file(file);
    switch (check) {
    case 1: {
        try {
            std::istream_iterator<Weapon> it(file);
            container.read(it);
        }
        catch (const std::runtime_error& ex) {
            std::cout << "End of input...\n";
        }
        catch (const std::invalid_argument& ex) {
            std::cout << "Read error! " << ex.what() << '\n';
        }
        break;
    }
    case 0: {
        std::cout << "\nContainer is empty!\n";
        break;
    }
    case -1: {
        std::cout << "\nFile open error!\n";
        break;
    }
    }
    file.close();
}


void print_in_console(Container<Weapon>& cont) {
    std::cout << "----------------\n";
    //std::ostream_iterator<Weapon>
    auto writer = std::ostream_iterator<Weapon>(std::cout, "----------------\n");
    cont.print(writer);
}

void print_in_file(Container<Weapon>& cont) {
    std::cin.ignore();

    std::cout << "\nEnter filename with extension:\n";
    std::string filename;
    std::getline(std::cin, filename);
    std::ofstream file(filename);
    //std::ostream_iterator<Weapon>
    auto writer = std::ostream_iterator<Weapon>(file);
    cont.print(writer);
    file.close();
    std::cout << "Data successfully written to file\n";
}

void select_from_name(Container<Weapon>& cont) {
    std::cout << "Enter start name range <std::string>:\n";
    std::string str1;
    std::cin.ignore();
    std::getline(std::cin, str1);
    std::cout << "Enter end name range <std::string>:\n";
    std::string str2;
    std::getline(std::cin, str2);
    Container<Weapon> selection = cont.selection([&str1, &str2](const Weapon& elem) {
        return elem.name >= str1 && elem.name <= str2;
        });
    if (!selection.empty()) {
        std::cout << "Select output method:\n1. Console\n2. File\n";
        int choice = validation("Enter valid value\n", 1, 2);
        if (choice == 1) {
            print_in_console(selection);
        }
        else {
            print_in_file(selection);
        }
    }
    else {
        std::cout << "Selection container is empty!\n";
    }
}

void select_from_type(Container<Weapon>& cont) {
    std::cout << "Enter weapon type <Pistol, Energy, Ranged, Explosive, Melee, OR Пистолет, Дальний бой,Взрывной, Энергетический>:\n";
    Type type;
    std::cin.ignore();
    if (!read_type(std::cin, type)) {
        throw std::invalid_argument("Invalid type!");
    }
    Container<Weapon> selection = cont.selection([&type](const Weapon& elem) {
        return elem.type == type;
        });
    if (!selection.empty()) {
        std::cout << "Select output method:\n1. Console\n2. File\n";
        int choice = validation("Enter valid value\n", 1, 2);
        if (choice == 1) {
            print_in_console(selection);
        }
        else {
            print_in_file(selection);
        }
    }
    else {
        std::cout << "Selection container is empty!\n";
    }
}

void change(Container<Weapon>& cont) {
    std::cout << "\nEnter index (0 <= i < " << cont.size() << ")\n";
    int id = validation("Enter valid index:\n", 0, cont.size() - 1);
    std::cout << "\nEnter data per template for replacement\n\n";
    show_template();
    Weapon new_w;
    std::cin >> new_w;
    if (cont.change(id, new_w)) {
        std::cout << "Success!\n";
    }
    else {
        std::cout << "Something went wrong!\n";
    }
}

void remove(Container<Weapon>& cont) {
    std::cout << "1. By index\n2. By value\n";
    int choice = validation("Enter valid menu option:\n", 1, 2);
    if (choice == 1) {
        std::cout << "\nEnter index (0 <= i < " << cont.size() << ")\n";
        int index = validation("Enter valid index:\n", 0, cont.size() - 1);
        if (cont.remove_by_index(index)) {
            std::cout << "Element successfully removed!\n";
        }
        else {
            std::cout << "No such element!\n";
        }
    }
    else {
        std::cout << "\nEnter data per template for removal\n\n";
        show_template();
        Weapon new_w;
        std::cin >> new_w;
        if (cont.remove_by_value(new_w)) {
            std::cout << "Element successfully removed!\n";
        }
        else {
            std::cout << "No such element!\n";
        }
    }
}

void get_weapon(Container<Weapon>& cont, Player& player) {
    std::cout << "\nEnter index (0 <= i < " << cont.size() << ")\n";
    int index = validation("Enter valid index (0 <= i < size):\n", 0, cont.size() - 1);
    std::cout << "\nEnter slot (1 <= i <= 3)\n";
    int slot = validation("Enter valid slot (1 <= i <= 3):\n", 1, 3);
    Weapon new_weapon = cont.get_index(index); 
    new_weapon.slot = slot;
    Weapon replaced = player.get(new_weapon); 
    cont.remove_by_index(index); 
    if (replaced.name != "")
    { 
        cont.add(replaced); 
        std::cout << "Previous weapon returned to inventory: " << replaced.name << "\n";
    }
    std::cout << "Weapon picked up successfully: " << new_weapon.name << "\n";
}

void drop_weapon(Container<Weapon>& cont, Player& player) {
    std::cout << "\nEnter slot (1 <= i <= 3)\n";
    int index = validation("Enter valid slot (1 <= i <= 3):\n", 1, 3);
    Weapon dropped = player.drop(index-1);
    if (dropped.name != "") {
        std::cout << "Success!\n";
        cont.add(dropped);
    }
    else {
        std::cout << "Slot is already empty!\n";
    }
}

void shot(Player& player) {
    std::cout << "\nEnter slot (1 <= i <= 3)\n";
    int index = validation("Enter valid slot (1 <= i <= 3):\n", 1, 3);
    if (player.shot(index - 1)) {
        std::cout << "Good shot!\n";
    }
    else {
        std::cout << "Slot empty or out of bullets!\n";
    }
}

int main() {
    Player player;
    Container<Weapon> cont;
    int main_choice;
    do {
        main_choice = Display_menu();
        try {
            switch (main_choice) {
            case 1: add_from_console(cont);
                break;
            case 2: add_from_file(cont);
                break;
            case 3: {
                if (!cont.empty()) {
                    cont.clear();
                    std::cout << "Container successfully cleared!\n";
                }
                else {
                    std::cout << "\nContainer is empty!\n";
                }
                break;
            }
            case 4: {
                if (!cont.empty()) {
                    print_in_console(cont);
                }
                else {
                    std::cout << "\nContainer is empty!\n";
                }
                break;
            }
            case 5: {
                if (!cont.empty()) {
                    print_in_file(cont);
                }
                else {
                    std::cout << "\nContainer is empty!\n";
                }
                break;
            }
            case 6: {
                if (!cont.empty()) {
                    remove(cont);
                }
                else {
                    std::cout << "\nContainer is empty!\n";
                }
                break;
            }
            case 7: {
                if (!cont.empty()) {
                    select_from_name(cont);
                }
                else {
                    std::cout << "\nContainer is empty!\n";
                }
                break;
            }
            case 8: {
                if (!cont.empty()) {
                    select_from_type(cont);
                }
                else {
                    std::cout << "\nContainer is empty!\n";
                }
                break;
            }
            case 9: {
                if (!cont.empty()) {
                    change(cont);
                }
                else {
                    std::cout << "\nContainer is empty!\n";
                }
                break;
            }
            case 10: {
                if (!cont.empty()) {
                    get_weapon(cont, player);
                }
                else {
                    std::cout << "\nContainer is empty!\n";
                }
                break;
            }
            case 11: {
                drop_weapon(cont,player);
                break;
            }
            case 12: {
                shot(player);
                break;
            }
            case 13: {
                if (!player.is_empty_slots()) {
                    player.show_hot_bar();
                }
                else {
                    std::cout << "All slots are empty\n";
                }
                break;
            }
            default: break;
            }
        }
        catch (const std::exception& ex) {
            std::cout << "Error: " << ex.what() << '\n';
            std::cin.clear();
            std::cin.ignore();
        }
    } while (main_choice != 14);

    return 0;
}