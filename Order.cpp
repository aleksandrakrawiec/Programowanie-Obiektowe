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

Person Order::getPerson()
{
	return _customer;
}

float Order::getValue()
{
	return _value;
}

void Order::addItem(Product item)
{
	_products.push_back(item);
    _value += item.getPrice();
}

void Order::showProducts()
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


void Order::showDetails()
{
	system("cls");
	cout << "DANE KLIENTA\n"
		<< "Imie: " << _customer.getFirstName()
		<< "\nNazwisko: " << _customer.getLastName()
		<< "\nNumer telefonu: " << _customer.getPhoneNumber()
        << "\n\nPRODUKTY\n";

	Program::UserInterface::showProductListHeaders();
    for (unsigned int i = 0; i < _products.size(); i++)
	{
		_products[i].printInfo();
	}
	cout << "\nLACZNA WARTOSC ZAMOWIENIA: " << _value;
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


void Order::constructNameByID()
{
    _name += std::to_string(_amount);
}
