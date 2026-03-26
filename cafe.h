#ifndef CAFE_H
#define CAFE_H

#include <iostream>
#include <fstream>
#include <cstring>

class Item {
private:
    int id;
    char name[50];
    float price;
    char category[30];

public:
    Item();
    Item(int id, const char* name, float price, const char* category);
    
    int getId() const;
    const char* getName() const;
    float getPrice() const;
    const char* getCategory() const;
    
    void setName(const char* name);
    void setPrice(float price);
    void setCategory(const char* category);
    
    friend std::ostream& operator<<(std::ostream& os, const Item& item);
    friend std::istream& operator>>(std::istream& is, Item& item);
};

class Menu {
private:
    Item* items;
    int count;
    int max;
    int next_id;
    
    void grow();

public:
    Menu();
    ~Menu();
    
    void load(const char* filename);
    void save(const char* filename);
    
    void show();
    void add();
    void edit();
    void search();
    void del();
    
    Item& operator[](int index);
    const Item& operator[](int index) const;
    
    int findById(int id) const;
};

#endif