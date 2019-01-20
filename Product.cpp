#include "Product.h"

using std::cout;
using std::string;

int Product::_amount = 0;

Product::Product() :
    _no(_amount + 1)
{

}

Product::Product(const string& name, float price, bool availability) :
    _no(_amount + 1),
	_name(name),
	_price(price),
    _availability(availability)
{

}

string Product::getName() const
{
	return _name;
}

void Product::setName(const std::string &name)
{
	_name = name;
}

float Product::getPrice() const
{
	return _price;
}

void Product::setPrice(float price)
{
	_price = price;
}

int Product::getNo() const
{
	return _no;
}

bool Product::getAvailability() const
{
	return _availability;
}

void Product::changeAvailability()
{
	_availability = !_availability;
}

void Product::printInfo() const
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

void Product::increaseProductsAmount()
{
    _amount++;
}

Product& Product::operator<<(const std::string &name)
{
    _name = name;

    return *this;
}

Product& Product::operator<<(float price)
{
    _price = price;

    return *this;
}

Product& Product::operator<<(bool availability)
{
    _availability = availability;

    return *this;
}

Product& Product::operator>>(std::string& name)
{
    name = _name;

    return *this;
}

Product& Product::operator>>(float& price)
{
    price = _price;

    return *this;
}

Product& Product::operator>>(bool& availability)
{
    availability = _availability;

    return *this;
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
