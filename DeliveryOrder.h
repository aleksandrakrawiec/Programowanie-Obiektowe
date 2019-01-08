#pragma once

#include "Order.h"

class DeliveryOrder : public Order
{
public:
    struct DeliveryAddress
        {
            std::string street;
            std::string number;
            std::string zipCode;
            std::string city;
        };

    DeliveryOrder(const Person &person, const DeliveryAddress &address);

protected:
    DeliveryAddress _address;

};
