#include "cafe.h"
#include <limits>

int getChoice() {
    int value;
    while (true) {
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Oshibka! Vvedite chislo: ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

void showMenu() {
    std::cout << "\n========== MENU ==========\n";
    std::cout << "1. Vyvesti vse\n";
    std::cout << "2. Dobavit\n";
    std::cout << "3. Redaktirovat\n";
    std::cout << "4. Nayti\n";
    std::cout << "5. Udalit\n";
    std::cout << "0. Vykhod\n";
    std::cout << "Vash vibor: ";
}

int main() {
    Menu cafe;
    cafe.load("db.txt");
    
    int choice;
    
    while (true) {
        showMenu();
        choice = getChoice();
        
        if (choice == 0) {
            cafe.save("db.txt");
            std::cout << "Vykhod...\n";
            break;
        }
        
        switch (choice) {
            case 1:
                cafe.show();
                break;
            case 2:
                cafe.add();
                break;
            case 3:
                cafe.edit();
                break;
            case 4:
                cafe.search();
                break;
            case 5:
                cafe.del();
                break;
            default:
                std::cout << "Nepravilniy vibor!\n";
        }
    }
    
    return 0;
}