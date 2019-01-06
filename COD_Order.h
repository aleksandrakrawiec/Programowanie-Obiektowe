#pragma once

#include "Order.h"

class COD_Order : public Order
{
public:
    COD_Order(const Person& person);

protected:
    void constructName() override;
};

