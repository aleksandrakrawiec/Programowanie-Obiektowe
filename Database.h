#pragma once

#include "Product.h"
#include "Order.h"

#include <vector>
#include <memory>

using OrderPtr = std::shared_ptr<Order>;

class Database
{
public:

    Database() = default;
    Database(const Database& copy);
    void operator=(const Database& copy);
    ~Database();

    bool addProduct(Product* product);
    void addOrder(OrderPtr order);

    std::vector<OrderPtr> getArchivalOrders() const;
    std::vector<OrderPtr> getActiveOrders() const;
    std::vector<Product*> getAllProducts() const;

    Product* getProduct(const std::string& name) const;
    Product* getProduct(int no) const;
    OrderPtr getOrder(int id);
    OrderPtr getOrder(const std::string& name) const;
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
    std::vector<OrderPtr> _orders;

    mutable int _tempArchivalOrdersCount;
    mutable int _tempActiveOrdersCount;
    mutable bool _isOrderListChanged = false;
};
