#pragma once

#include "Person.h"
#include "Product.h"

#include <vector>

class Order
{

public:
    Order(const Person& customer);

	Person getPerson();
	float getValue();
	void addItem(Product item);
	void showProducts();
    void showOrder() const;
	void showDetails();
	void makeArchival();
    bool isActive() const;

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

