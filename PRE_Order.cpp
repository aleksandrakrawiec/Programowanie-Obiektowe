#include "PRE_Order.h"

PRE_Order::PRE_Order(const Person &person) :
    Order(person)
{
    constructName();
}

void PRE_Order::constructName()
{
    _name += "PRE" + std::to_string(_amount);
}
