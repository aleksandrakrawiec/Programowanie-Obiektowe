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

    friend std::ostream& operator<<(std::ostream& stream, const Order& order);
    Product& operator[](int index);

protected:
    std::vector <Product> _products;
    Person _customer;
    float _value = 0;
    int _no;
    std::string _name;
    bool _active = true;
    static int _amount;

    virtual void constructName() = 0;

private:
    void constructNameByID();
};

