#pragma once

#include "DeliveryOrder.h"

class PRE_Order : public DeliveryOrder
{
public:
    PRE_Order(const Person& person);

protected:
    void constructName() override;
};
