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
    virtual void showDetails() const;
    void showAddress() const;
    DeliveryAddress getAddress() const;


protected:
    DeliveryAddress _address;
};

std::ostream& operator<<(std::ostream& stream, const DeliveryOrder::DeliveryAddress& address);
