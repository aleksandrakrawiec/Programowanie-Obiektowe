#include "DeliveryOrder.h"
#include "Program.h"

using std::cout;
using std::string;

DeliveryOrder::DeliveryOrder(const Person &person, const DeliveryAddress &address) :
    Order(person), _address(address)
{

}

void DeliveryOrder::showDetails() const
{
    system("cls");
    cout << "Zamowienie " << _name << "\n\n";
    cout << "DANE KLIENTA\n";
    _customer.showPerson();

    cout << "\n\nADRES\n";
    showAddress();

    cout << "\n\nPRODUKTY\n";

    Program::UserInterface::showProductListHeaders();
    for (unsigned int i = 0; i < _products.size(); i++)
    {
        _products[i]->printInfo();
    }
    cout << "\nLACZNA WARTOSC ZAMOWIENIA: " << _value << "\n";
}

void DeliveryOrder::showAddress() const
{
    cout << _address.street << " " << _address.number << "\n"
         << _address.zipCode << " " << _address.city << "\n";
}

DeliveryOrder::DeliveryAddress DeliveryOrder::getAddress() const
{
    return _address;
}

std::ostream& operator<<(std::ostream &stream, const DeliveryOrder::DeliveryAddress &address)
{
    stream << address.street << std::endl;
    stream << address.number << std::endl;
    stream << address.zipCode << std::endl;
    stream << address.city;

    return stream;
}
