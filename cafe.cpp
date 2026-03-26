#include "cafe.h"
#include <limits>

Item::Item() : id(0), price(0) {
    name[0] = '\0';
    category[0] = '\0';
}

Item::Item(int id, const char* name, float price, const char* category) : id(id), price(price) {
    strcpy(this->name, name);
    strcpy(this->category, category);
}

int Item::getId() const {
    return id;
}

const char* Item::getName() const {
    return name;
}

float Item::getPrice() const {
    return price;
}

const char* Item::getCategory() const {
    return category;
}

void Item::setName(const char* name) {
    strcpy(this->name, name);
}

void Item::setPrice(float price) {
    this->price = price;
}

void Item::setCategory(const char* category) {
    strcpy(this->category, category);
}

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << item.id << " " << item.name << " " << item.price << " [" << item.category << "]";
    return os;
}

std::istream& operator>>(std::istream& is, Item& item) {
    is >> item.id >> item.name >> item.price >> item.category;
    return is;
}

Menu::Menu() : items(nullptr), count(0), max(10), next_id(1) {
    items = new Item[max];
}

Menu::~Menu() {
    delete[] items;
}

void Menu::grow() {
    max = max * 2;
    Item* new_items = new Item[max];
    for (int i = 0; i < count; i++) {
        new_items[i] = items[i];
    }
    delete[] items;
    items = new_items;
}

void Menu::load(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    
    int id;
    char name[50];
    float price;
    char category[30];
    
    while (file >> id >> name >> price >> category) {
        if (count >= max) grow();
        items[count] = Item(id, name, price, category);
        count++;
        if (id >= next_id) next_id = id + 1;
    }
    
    file.close();
}

void Menu::save(const char* filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Oshibka sohraneniya!\n";
        return;
    }
    
    for (int i = 0; i < count; i++) {
        file << items[i].getId() << " "
             << items[i].getName() << " "
             << items[i].getPrice() << " "
             << items[i].getCategory() << "\n";
    }
    
    file.close();
}

void Menu::show() {
    if (count == 0) {
        std::cout << "Spisok pust\n";
        return;
    }
    
    for (int i = 0; i < count; i++) {
        std::cout << items[i] << std::endl;
    }
}

int Menu::findById(int id) const {
    for (int i = 0; i < count; i++) {
        if (items[i].getId() == id) return i;
    }
    return -1;
}

float inputFloat(const char* prompt) {
    float value;
    while (true) {
        std::cout << prompt;
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

int inputInt(const char* prompt) {
    int value;
    while (true) {
        std::cout << prompt;
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

void Menu::add() {
    if (count >= max) grow();
    
    char name[50];
    float price;
    char category[30];
    
    std::cout << "Vvedite nazvanie: ";
    std::cin >> name;
    
    price = inputFloat("Vvedite cenu: ");
    
    std::cout << "Vvedite kategoriyu: ";
    std::cin >> category;
    
    items[count] = Item(next_id, name, price, category);
    count++;
    next_id++;
    
    std::cout << "Dobavleno! ID: " << (next_id - 1) << std::endl;
    save("db.txt");
}

void Menu::edit() {
    int id = inputInt("Vvedite ID: ");
    
    int index = findById(id);
    if (index == -1) {
        std::cout << "Ne naideno!\n";
        return;
    }
    
    char name[50];
    float price;
    char category[30];
    
    std::cout << "Staroe nazvanie: " << items[index].getName() << std::endl;
    std::cout << "Novoe nazvanie: ";
    std::cin >> name;
    
    price = inputFloat("Novaya cena: ");
    
    std::cout << "Staraya kategoriya: " << items[index].getCategory() << std::endl;
    std::cout << "Novaya kategoriya: ";
    std::cin >> category;
    
    items[index].setName(name);
    items[index].setPrice(price);
    items[index].setCategory(category);
    
    std::cout << "Izmeneno!\n";
    save("db.txt");
}

void Menu::search() {
    int choice = inputInt("\n--- Poisk ---\n1 - po ID\n2 - po cene (do)\n3 - po kategorii\nVash vibor: ");
    
    if (choice == 1) {
        int id = inputInt("Vvedite ID: ");
        
        int index = findById(id);
        if (index == -1) {
            std::cout << "Ne naideno!\n";
        } else {
            std::cout << items[index] << std::endl;
        }
    }
    else if (choice == 2) {
        float max_price = inputFloat("Maksimalnaya cena: ");
        
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (items[i].getPrice() <= max_price) {
                std::cout << items[i] << std::endl;
                found = true;
            }
        }
        if (!found) std::cout << "Ne naideno!\n";
    }
    else if (choice == 3) {
        char category[30];
        std::cout << "Vvedite kategoriyu: ";
        std::cin >> category;
        
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (strcmp(items[i].getCategory(), category) == 0) {
                std::cout << items[i] << std::endl;
                found = true;
            }
        }
        if (!found) std::cout << "Ne naideno!\n";
    }
    else {
        std::cout << "Nepravilniy vibor!\n";
    }
}

void Menu::del() {
    int id = inputInt("Vvedite ID: ");
    
    int index = findById(id);
    if (index == -1) {
        std::cout << "Ne naideno!\n";
        return;
    }
    
    for (int i = index; i < count - 1; i++) {
        items[i] = items[i + 1];
    }
    count--;
    
    std::cout << "Udaleno!\n";
    save("db.txt");
}

Item& Menu::operator[](int index) {
    return items[index];
}

const Item& Menu::operator[](int index) const {
    return items[index];
}