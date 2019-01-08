#include "Order.h"
#include "Program.h"

using std::cout;
using std::string;

int Order::_amount = 0;

Order::Order(const Person &customer) :
    _customer(customer),
    _no(_amount + 1)
{
    _amount++;
}

Person Order::getPerson() const
{
	return _customer;
}

float Order::getValue() const
{
	return _value;
}

void Order::addItem(const Product& item)
{
	_products.push_back(item);
    _value += item.getPrice();
}

void Order::showProducts() const
{
	cout.width(20);
	cout << "Nazwa produktu";
	cout.width(10);
	cout << "Cena";

    for (unsigned int i = 0; i < _products.size(); i++)
	{
		cout.width(20);
        cout << _products[i].getName();
		cout.width(10);
        cout << _products[i].getPrice();
	}
}

void Order::showOrder() const
{
	cout.width(10);
	cout << _no;
    cout.width(10);
    cout << _name;
	cout.width(20);
	cout << _customer.getFirstName();
	cout.width(20);
	cout << _customer.getLastName();
	cout.width(10);
	cout << _value << "\n";
}

std::ostream& operator<<(std::ostream& stream, const Order& order)
{
    stream.width(10);
    stream << order._no;

    stream.width(10);
    stream << order._name;

    stream.width(20);
    stream << order._customer.getFirstName();

    stream.width(20);
    stream << order._customer.getLastName();

    stream.width(10);
    stream << order._value << "\n";

    return stream;
}

void Order::showDetails() const
{
	system("cls");
    cout << "Zamowienie " << _name << "\n\n";
    cout << "DANE KLIENTA\n";
    _customer.showPerson();

    cout << "\n\nPRODUKTY\n";

	Program::UserInterface::showProductListHeaders();
    for (unsigned int i = 0; i < _products.size(); i++)
	{
		_products[i].printInfo();
	}
    cout << "\nLACZNA WARTOSC ZAMOWIENIA: " << _value << "\n";
}

void Order::makeArchival()
{
	_active = false;
}

bool Order::isActive() const
{
    return _active;
}

Product& Order::operator[](int index)
{
    return _products[index];
}
