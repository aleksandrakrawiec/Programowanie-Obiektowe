#include "DeliveryOrder.h"

DeliveryOrder::DeliveryOrder(const Person &person, const DeliveryAddress &address) :
    Order(person), _address(address)
{

}
