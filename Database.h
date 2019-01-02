#pragma once

#include "Product.h"
#include "Order.h"

#include <vector>
#include <memory>

//using ProductPtr = std::unique_ptr<Product>;

class Database
{
public:
    ~Database();
    bool addProduct(Product* product);
    void addOrder(const Order& order);

    std::vector<Order> getArchivalOrders() const;
    std::vector<Order> getActiveOrders() const;
    std::vector<Product*> getAllProducts() const;

    Product* getProduct(const std::string& name) const;
    Product* getProduct(int no) const;
    Order& getOrder(int no);

private:
    std::vector<Product*> _products;
    std::vector<Order> _orders;
};
