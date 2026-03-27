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

int main(int argc, char* argv[]) {
    Menu cafe;
    
    std::string filename;
    if (argc >= 2) {
        filename = argv[1];
    } else {
        std::cout << "Vvedite imya faila: ";
        std::cin >> filename;
    }
    
    cafe.load(filename);
    
    int choice;
    
    while (true) {
        showMenu();
        choice = getChoice();
        
        if (choice == 0) {
            cafe.save();
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
                cafe.find();
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
