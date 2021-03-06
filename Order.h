#pragma once

#include "Person.h"
#include "Product.h"

#include <iostream>
#include <vector>

class Order
{

public:
    Order(const Person& customer);
    virtual ~Order() = default;

    Person getPerson() const;
    float getValue() const;
    std::string getName() const;
    void addItem(Product *item);
    void showProducts() const;
    void showOrder() const;
    virtual void showDetails() const;
	void makeArchival();
    bool isActive() const;
    int getProductsCount() const;

    int getArchivalOrdersCount() const;
    int getActiveOrdersCount() const;

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
    const Product& operator[](int index) const;

protected:
    std::vector <Product*> _products;
    Person _customer;
    float _value = 0;
    std::string _name;
    bool _active = true;
    static int _amount;

    virtual void constructName() = 0;

private:
    void constructNameByID();
};
