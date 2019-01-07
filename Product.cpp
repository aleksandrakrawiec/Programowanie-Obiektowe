#include "Product.h"



using std::cout;
using std::string;

int Product::_amount = 0;

Product::Product() {}

Product::Product(string name, float price) :
    _no(_amount + 1),
	_name(name),
	_price(price),
	_availability(true)
{
}

string Product::getName()
{
	return _name;
}

void Product::setName(string name)
{
	_name = name;
}

float Product::getPrice()
{
	return _price;
}

void Product::setPrice(float price)
{
	_price = price;
}

int Product::getNo()
{
	return _no;
}

bool Product::getAvailability()
{
	return _availability;
}

void Product::changeAvailability()
{
	_availability = !_availability;
}

void Product::printInfo()
{
	cout.width(8);
	cout << _no;
	cout.width(20);
	cout << _name;
    cout.width(10);
	cout << _price;
	cout.width(15);
	_availability == true ? std::cout << "dostepny\n" : std::cout << "niedostepny\n";
}

std::ostream& operator<< (std::ostream& stream, const Product& product)
{
    stream.width(8);
    stream << product._no;

    stream.width(20);
    stream << product._name;

    stream.width(10);
    stream << product._price;

    cout.width(15);
    product._availability == true ? stream << "dostepny\n" : stream << "niedostepny\n";

    return stream;
}
