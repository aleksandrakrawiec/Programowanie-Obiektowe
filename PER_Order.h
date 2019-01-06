#pragma once

#include "Order.h"


class PER_Order : public Order
{
public:
    PER_Order(const Person &person);

protected:
    void constructName() override;
};
