#include "Database.h"

#include <algorithm>

Database::~Database()
{
    for (auto productPtr : _products)
    {
        delete productPtr;
    }
}

bool Database::addProduct(Product *product)
{
    Product* productWithTheSameName = getProduct(product->getName());

    if (productWithTheSameName != nullptr)
    {
        return false;
    }

    _products.push_back(product);
    Product::_amount++; // nie wiem czy to jest ok
    return true;
}

void Database::addOrder(const Order& order)
{
    _orders.push_back(order);
}

std::vector<Order> Database::getArchivalOrders() const
{
    std::vector<Order> result;

    for (const auto& order : _orders)
    {
        if (!order.isActive())
        {
            result.push_back(order);
        }
    }

    return result;
}

std::vector<Order> Database::getActiveOrders() const
{
    std::vector<Order> result;

    for (const auto& order : _orders)
    {
        if (order.isActive())
        {
            result.push_back(order);
        }
    }

    return result;
}


std::vector<Product *> Database::getAllProducts() const
{
    return _products;
}

Product *Database::getProduct(const std::string &name) const
{
    auto foundPosition = std::find_if(_products.begin(), _products.end(), [name](Product* p){
        return (p->getName() == name);
    });

    if (foundPosition == _products.end())
        return nullptr;

    return *foundPosition;
}

Product *Database::getProduct(int no) const
{
    auto foundPosition = std::find_if(_products.begin(), _products.end(), [no](Product* p){
        return (p->getNo() == no);
    });

    if (foundPosition == _products.end())
        return nullptr;

    return *foundPosition;
}

Order &Database::getOrder(int no)
{
    return _orders[no];

}
