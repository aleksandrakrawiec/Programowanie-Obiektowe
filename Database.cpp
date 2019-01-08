#include "Database.h"

#include <algorithm>
#include <fstream>
#include <cstdlib>

const std::string FILENAME = "database";

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

    Product::increaseProductsAmount();

//    saveToFile();

    return true;
}

void Database::addOrder(Order *order)
{
    _orders.push_back(order);

    saveToFile();
}

std::vector<Order *> Database::getArchivalOrders() const
{
    std::vector<Order*> result;

    for (auto order : _orders)
    {
        if (!order->isActive())
        {
            result.push_back(order);
        }
    }

    return result;
}

std::vector<Order *> Database::getActiveOrders() const
{
    std::vector<Order*> result;

    for (auto order : _orders)
    {
        if (order->isActive())
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

Order* Database::getOrder(int id)
{
    return _orders[id];

}

bool Database::saveToFile() const
{
    std::ofstream file(FILENAME);

    if (!file.is_open())
        return false;

    // write products count
    file << _products.size() << std::endl;

    // writing product to file packed into lambda
    // because there's no need to create global function
    // because it will be used only inside this method
    auto writeProductToFile = [&file](Product* product) {
        string name;
        float price;
        bool availability;

        // get product data
        *product >> name >> price >> availability;

        // write it to file
        file << name << std::endl;
        file << price << std::endl;
        file << availability << std::endl;
    };

    // write data of all products
    for (const auto& product : _products)
    {
        writeProductToFile(product);
    }

    // write orders count
    file << _orders.size() << std::endl;

    // write data of all orders
    for (auto order : _orders)
    {
        Person customer;
        string name;
        float value;
        bool active;

        // get order 'single' data
        *order >> customer >> name >> value >> active;

        // write it to file
        file << customer.getFirstName() << std::endl;
        file << customer.getLastName() << std::endl;
        file << customer.getPhoneNumber() << std::endl;
        file << name << std::endl;
        file << value << std::endl;
        file << active << std::endl;

        int productsCount = order->getProductsCount();
        file << productsCount << std::endl;

        for (int i = 0; i < productsCount; ++i)
        {
            Product& product = (*order)[i];
            writeProductToFile(&product);
        }

    }

    file.close();
    return true;
}

bool Database::loadFromFile()
{
    std::ifstream file(FILENAME);

    // something went wrong, return false
    if (!file.is_open())
        return false;

    // clear all products
    _products.clear();

    // it's gonna store every read line
    std::string input;

    // read products count
    std::getline(file, input);
    int productCount = std::stoi(input);

    auto loadProductFromFile = [this, &file, &input]() {
        // read name, price and availability
        std::getline(file, input);
        string name = input;

        std::getline(file, input);
        float price = atof(input.c_str());

        std::getline(file, input);
        bool availability = static_cast<bool>(std::stoi(input));

        // create product and write values to it
        Product* product = new Product();
        *product << name << price << availability;

        return product;
    };

    for (int i = 0; i < productCount; ++i)
    {
        Product* product = loadProductFromFile();

        // use this method to ensure correct product insertion
        addProduct(product);
    }

    // read orders count
    std::getline(file, input);
    int ordersCount = std::stoi(input);

    for (int i = 0; i < ordersCount; ++i)
    {
        std::getline(file, input);
        string customerFirstName = input;

        std::getline(file, input);
        string customerLastName = input;

        std::getline(file, input);
        int customerPhoneNumber = std::stoi(input);

        std::getline(file, input);
        string name = input;

        std::getline(file, input);
        float value = atof(input.c_str());

        std::getline(file, input);
        bool active = static_cast<bool>(std::stoi(input));

        Person customer(customerFirstName, customerLastName, customerPhoneNumber);

//        Order* order = new Order(customer);

//        *order << name << value << active;

//        std::getline(file, input);
//        int productsCount = input;

//        for (int i = 0; i < productCount; ++i)
//        {

//        }

    }


    return true;
}
