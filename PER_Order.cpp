#include "PER_Order.h"

PER_Order::PER_Order(const Person &person) :
    Order(person)
{
    constructName();
}

void PER_Order::constructName()
{
    _name += "PER" + std::to_string(_amount);
}
