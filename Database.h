#pragma once

#include "Product.h"
#include "Order.h"

#include <vector>
#include <memory>

//using ProductPtr = std::unique_ptr<Product>;

//using OrderPtr = std::unique_ptr<Order>;

class Database
{
public:
    Database() = default;
    Database(const Database& copy);
    void operator=(const Database& copy);
    ~Database();
    bool addProduct(Product* product);
    void addOrder(Order* order);

    std::vector<Order*> getArchivalOrders() const;
    std::vector<Order*> getActiveOrders() const;
    std::vector<Product*> getAllProducts() const;

    Product* getProduct(const std::string& name) const;
    Product* getProduct(int no) const;
    Order* getOrder(int id);
    int getOrdersCount() const;
    int getArchivalOrdersCount() const;
    int getActiveOrdersCount() const;

    void orderListChaged();

    bool saveToFile() const;
    bool loadFromFile();

private:
    enum OrderType
    {
        COD_OrderType,
        PRE_OrderType,
        PER_OrderType
    };

    std::vector<Product*> _products;
    std::vector<Order*> _orders;

    mutable int _tempArchivalOrdersCount;
    mutable int _tempActiveOrdersCount;
    mutable bool _isOrderListChanged = false;
};
