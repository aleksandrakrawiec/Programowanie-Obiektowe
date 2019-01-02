#pragma once

#include "Person.h"
#include "Product.h"

#include <vector>

class Order
{
	std::vector <Product> _products;
	Person _customer;
	float _value = 0;
	int _no;
	bool _active = true;

public:
	static int _amount;
	Order();
	Order(Person customer);
	~Order();
	Person getPerson();
	float getValue();
	void addItem(Product item);
	void showProducts();
    void showOrder() const;
	void showDetails();
	void makeArchival();
    bool isActive() const;
};

