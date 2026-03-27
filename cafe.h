#ifndef CAFE_H
#define CAFE_H

#include <iostream>
#include <fstream>
#include <string>

class Item {
private:
    int id;
    std::string name;
    float price;
    std::string category;
    Item* next;

public:
    Item();
    Item(int id, const std::string& name, float price, const std::string& category);
    
    int getId() const;
    std::string getName() const;
    float getPrice() const;
    std::string getCategory() const;
    Item* getNext() const;
    
    void setName(const std::string& name);
    void setPrice(float price);
    void setCategory(const std::string& category);
    void setNext(Item* next);
    
    friend std::ostream& operator<<(std::ostream& os, const Item& item);
    friend std::istream& operator>>(std::istream& is, Item& item);
};

class Menu {
private:
    Item* head;
    int next_id;
    std::string filename;

public:
    Menu();
    ~Menu();
    
    void load(const std::string& filename);
    void save();
    
    void show();
    void add();
    void edit();
    void find();
    void del();
    
    Item* findById(int id) const;
};

#endif
