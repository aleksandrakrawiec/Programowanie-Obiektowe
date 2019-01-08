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
    ~Database();
    bool addProduct(Product* product);
    void addOrder(Order* order);

    std::vector<Order*> getArchivalOrders() const;
    std::vector<Order*> getActiveOrders() const;
    std::vector<Product*> getAllProducts() const;

    Product* getProduct(const std::string& name) const;
    Product* getProduct(int no) const;
    Order* getOrder(int id);

    bool saveToFile() const;
    bool loadFromFile();

private:
    std::vector<Product*> _products;
    std::vector<Order*> _orders;
};
