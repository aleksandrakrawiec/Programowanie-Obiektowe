#pragma once

#include "DeliveryOrder.h"


class COD_Order : public DeliveryOrder
{
public:
    COD_Order(const Person& person);

protected:
    void constructName() override;
};

