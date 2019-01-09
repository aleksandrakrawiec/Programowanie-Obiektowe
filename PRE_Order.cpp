#include "PRE_Order.h"

PRE_Order::PRE_Order(const Person &person, const DeliveryAddress &address) :
    DeliveryOrder(person, address)
{
    constructName();
}

void PRE_Order::constructName()
{
    _name += "PRE" + std::to_string(_amount);
}
