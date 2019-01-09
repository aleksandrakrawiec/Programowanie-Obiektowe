#include "COD_Order.h"

COD_Order::COD_Order(const Person &person, const DeliveryAddress &address) :
    DeliveryOrder(person, address)
{
    constructName();
}

void COD_Order::constructName()
{
    _name += "COD" + std::to_string(_amount);
}
