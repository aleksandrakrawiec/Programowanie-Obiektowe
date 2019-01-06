#pragma once

#include "Order.h"

class PRE_Order : public Order
{
public:
    PRE_Order(const Person& person);

protected:
    void constructName() override;
};
