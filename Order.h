#pragma once

#include "Person.h"
#include "Product.h"

#include <iostream>
#include <vector>

class Order
{
public:
    Order(const Person& customer);

    Person getPerson() const;
    float getValue() const;
    void addItem(const Product &item);
    void showProducts() const;
    void showOrder() const;
    void showDetails() const;
	void makeArchival();
    bool isActive() const;
    int getProductsCount() const;

    friend std::ostream& operator<<(std::ostream& stream, const Order& order);

//    friend std::ostream& operator<<(std::ostream& stream, const Person& person);


    Order& operator<< (const Person& customer);
    Order& operator<< (const std::string& name);
    Order& operator<< (float value);
    Order& operator<< (bool active);

    Order& operator>> (Person& customer);
    Order& operator>> (std::string& name);
    Order& operator>> (float& value);
    Order& operator>> (bool& active);

    Product& operator[](int index);
    const Product& operator[](int index) const; // for const objects

protected:
    std::vector <Product> _products;
    Person _customer;
    float _value = 0;
    int _no;
    std::string _name;
    bool _active = true;
    static int _amount;

    virtual void constructName() = 0;
};

