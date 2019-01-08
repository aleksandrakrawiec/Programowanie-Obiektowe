#pragma once

#include "DeliveryOrder.h"

class PRE_Order : public DeliveryOrder
{
public:
    PRE_Order(const Person& person, const DeliveryAddress &address);

protected:
    void constructName() override;
};
