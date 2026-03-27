#include "cafe.h"
#include <limits>

Item::Item() : id(0), price(0), next(nullptr) {}

Item::Item(int id, const std::string& name, float price, const std::string& category)
    : id(id), name(name), price(price), category(category), next(nullptr) {}

int Item::getId() const { return id; }
std::string Item::getName() const { return name; }
float Item::getPrice() const { return price; }
std::string Item::getCategory() const { return category; }
Item* Item::getNext() const { return next; }

void Item::setName(const std::string& n) { name = n; }
void Item::setPrice(float p) { price = p; }
void Item::setCategory(const std::string& c) { category = c; }
void Item::setNext(Item* n) { next = n; }

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << item.id << " " << item.name << " " << item.price << " [" << item.category << "]";
    return os;
}

std::istream& operator>>(std::istream& is, Item& item) {
    is >> item.id >> item.name >> item.price >> item.category;
    return is;
}

Menu::Menu() : head(nullptr), next_id(1) {}

Menu::~Menu() {
    Item* current = head;
    while (current != nullptr) {
        Item* temp = current;
        current = current->getNext();
        delete temp;
    }
}

void Menu::load(const std::string& fname) {
    filename = fname;
    std::ifstream file(filename);
    if (!file.is_open()) return;
    
    int id;
    std::string name;
    float price;
    std::string category;
    
    Item* last = nullptr;
    
    while (file >> id >> name >> price >> category) {
        Item* new_item = new Item(id, name, price, category);
        
        if (head == nullptr) {
            head = new_item;
        } else {
            last->setNext(new_item);
        }
        last = new_item;
        
        if (id >= next_id) {
            next_id = id + 1;
        }
    }
    
    file.close();
}

void Menu::save() {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Oshibka sohraneniya!\n";
        return;
    }
    
    Item* current = head;
    while (current != nullptr) {
        file << current->getId() << " "
             << current->getName() << " "
             << current->getPrice() << " "
             << current->getCategory() << "\n";
        current = current->getNext();
    }
    
    file.close();
}

void Menu::show() {
    if (head == nullptr) {
        std::cout << "Spisok pust\n";
        return;
    }
    
    Item* current = head;
    while (current != nullptr) {
        std::cout << *current << std::endl;
        current = current->getNext();
    }
}

Item* Menu::findById(int id) const {
    Item* current = head;
    while (current != nullptr) {
        if (current->getId() == id) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

float inputFloat(const std::string& prompt) {
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

int inputInt(const std::string& prompt) {
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
    std::string name, category;
    float price;
    
    std::cout << "Vvedite nazvanie: ";
    std::cin >> name;
    
    price = inputFloat("Vvedite cenu: ");
    
    std::cout << "Vvedite kategoriyu: ";
    std::cin >> category;
    
    Item* new_item = new Item(next_id, name, price, category);
    next_id++;
    
    if (head == nullptr) {
        head = new_item;
    } else {
        Item* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(new_item);
    }
    
    std::cout << "Dobavleno! ID: " << (next_id - 1) << std::endl;
    save();
}

void Menu::edit() {
    int id = inputInt("Vvedite ID: ");
    
    Item* item = findById(id);
    if (item == nullptr) {
        std::cout << "Ne naideno!\n";
        return;
    }
    
    std::string name, category;
    float price;
    
    std::cout << "Staroe nazvanie: " << item->getName() << std::endl;
    std::cout << "Novoe nazvanie: ";
    std::cin >> name;
    
    price = inputFloat("Novaya cena: ");
    
    std::cout << "Staraya kategoriya: " << item->getCategory() << std::endl;
    std::cout << "Novaya kategoriya: ";
    std::cin >> category;
    
    item->setName(name);
    item->setPrice(price);
    item->setCategory(category);
    
    std::cout << "Izmeneno!\n";
    save();
}

void Menu::find() {
    int choice = inputInt("\n--- Poisk ---\n1 - po ID\n2 - po cene (do)\n3 - po kategorii\nVash vibor: ");
    
    if (choice == 1) {
        int id = inputInt("Vvedite ID: ");
        
        Item* item = findById(id);
        if (item == nullptr) {
            std::cout << "Ne naideno!\n";
        } else {
            std::cout << *item << std::endl;
        }
    }
    else if (choice == 2) {
        float max_price = inputFloat("Maksimalnaya cena: ");
        
        bool found = false;
        Item* current = head;
        while (current != nullptr) {
            if (current->getPrice() <= max_price) {
                std::cout << *current << std::endl;
                found = true;
            }
            current = current->getNext();
        }
        if (!found) std::cout << "Ne naideno!\n";
    }
    else if (choice == 3) {
        std::string category;
        std::cout << "Vvedite kategoriyu: ";
        std::cin >> category;
        
        bool found = false;
        Item* current = head;
        while (current != nullptr) {
            if (current->getCategory() == category) {
                std::cout << *current << std::endl;
                found = true;
            }
            current = current->getNext();
        }
        if (!found) std::cout << "Ne naideno!\n";
    }
    else {
        std::cout << "Nepravilniy vibor!\n";
    }
}

void Menu::del() {
    int id = inputInt("Vvedite ID: ");
    
    if (head == nullptr) {
        std::cout << "Spisok pust\n";
        return;
    }
    
    if (head->getId() == id) {
        Item* temp = head;
        head = head->getNext();
        delete temp;
        std::cout << "Udaleno!\n";
        save();
        return;
    }
    
    Item* current = head;
    while (current->getNext() != nullptr) {
        if (current->getNext()->getId() == id) {
            Item* temp = current->getNext();
            current->setNext(current->getNext()->getNext());
            delete temp;
            std::cout << "Udaleno!\n";
            save();
            return;
        }
        current = current->getNext();
    }
    
    std::cout << "Ne naideno!\n";
}
