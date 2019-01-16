#include "Database.h"

#include "COD_Order.h"
#include "PER_Order.h"
#include "PRE_Order.h"

#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <typeinfo>

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
//    auto foundPosition = std::find_if(_products.begin(), _products.end(), [name](Product* p){
//        return (p->getName() == name);
//    });

    auto foundPosition = std::find_if(_products.begin(), _products.end(), Product::CompareByName(name));

    if (foundPosition == _products.end())
        return nullptr;

    return *foundPosition;
}

Product *Database::getProduct(int no) const
{
//    auto foundPosition = std::find_if(_products.begin(), _products.end(), [no](Product* p){
//        return (p->getNo() == no);
//    });

    auto foundPosition = std::find_if(_products.begin(), _products.end(), Product::CompareByNumber(no));

    if (foundPosition == _products.end())
        return nullptr;

    return *foundPosition;
}

Order* Database::getOrder(int id)
{
    return _orders[id];
}

int Database::getOrdersCount() const
{
    return _orders.size();
}

bool Database::saveToFile() const
{
    std::ofstream file(FILENAME);

    if (!file.is_open())
        return false;

    file << _products.size() << std::endl;

    for (const auto& product : _products)
    {
        string name;
        float price;
        bool availability;

        *product >> name >> price >> availability;

        file << name << std::endl;
        file << price << std::endl;
        file << availability << std::endl;
    }

    file << _orders.size() << std::endl;

    for (auto order : _orders)
    {
        // typeid działa po dodaniu headera <typeinfo>
        OrderType orderType;

        if (typeid(*order) == typeid(COD_Order))
        {
            file << COD_OrderType << std::endl; // 0
            orderType = COD_OrderType;
        }
        else if (typeid(*order) == typeid(PRE_Order))
        {
            file << PRE_OrderType << std::endl; // 1
            orderType = PRE_OrderType;
        }
        else if (typeid(*order) == typeid(PER_Order))
        {
            file << PER_OrderType << std::endl; // 2
            orderType = PER_OrderType;
        }
        else
        {
            return false;
        }

        Person customer;
        string name;
        bool active;

        *order >> customer >> name >> active;

        file << customer << std::endl;
        file << name << std::endl;
        file << active << std::endl;

        if (orderType != PER_OrderType)
        {
            DeliveryOrder* deliveryOrder = dynamic_cast<DeliveryOrder*>(order);  // rzutowanie

            if (deliveryOrder == nullptr)
                return false;

            file << deliveryOrder->getAddress() << std::endl;
        }

        int productsCount = order->getProductsCount();
        file << productsCount << std::endl;

        for (int i = 0; i < productsCount; ++i)
        {

            int productNumber = (*order)[i].getNo();
            file << productNumber << std::endl;
        }
    }

    file.close();
    return true;
}

bool Database::loadFromFile()
{
    std::ifstream file(FILENAME);

    if (!file.is_open())
        return false;

    file.seekg(0, file.end);
    if (file.tellg() == 0)
        return true;

    file.seekg(0, file.beg);

    _products.clear();
    _orders.clear();

    std::string input;

    std::getline(file, input);
    int productCount = std::stoi(input);

    auto loadProductFromFile = [this, &file, &input]() {
        std::getline(file, input);
        string name = input;

        std::getline(file, input);
        float price = atof(input.c_str());

        std::getline(file, input);
        bool availability = static_cast<bool>(std::stoi(input));

        Product* product = new Product();
        *product << name << price << availability;

        return product;
    };

    for (int i = 0; i < productCount; ++i)
    {
        Product* product = loadProductFromFile();

        addProduct(product);
    }

    std::getline(file, input);
    int ordersCount = std::stoi(input);

    for (int i = 0; i < ordersCount; ++i)
    {
        std::getline(file, input);
        // rzutowanie int na enuma
        OrderType orderType = static_cast<OrderType>(std::stoi(input));

        std::getline(file, input);
        string customerFirstName = input;

        std::getline(file, input);
        string customerLastName = input;

        std::getline(file, input);
        int customerPhoneNumber = std::stoi(input);

        std::getline(file, input);
        string name = input;


        std::getline(file, input);
        // rzutowanie int na boola
        bool active = static_cast<bool>(std::stoi(input));

        Person customer(customerFirstName, customerLastName, customerPhoneNumber);

        DeliveryOrder::DeliveryAddress address;
        if (orderType != PER_OrderType)
        {
            std::getline(file, input);
            address.street = input;

            std::getline(file, input);
            address.number = input;

            std::getline(file, input);
            address.zipCode = input;

            std::getline(file, input);
            address.city = input;
        }

        Order* order;

        switch (orderType)
        {
        case COD_OrderType:
            order = new COD_Order(customer, address);
            break;
        case PRE_OrderType:
            order = new PRE_Order(customer, address);
            break;
        case PER_OrderType:
            order = new PER_Order(customer);
            break;
        default:
            return false;
        }

        *order << name << active;

        std::getline(file, input);
        int productsCount = std::stoi(input);

        for (int i = 0; i < productsCount; ++i)
        {
            std::getline(file, input);
            int productNumber = std::stoi(input);

            Product* product = getProduct(productNumber);

            if (product == nullptr)
                return false;

            order->addItem(*product);
        }

        addOrder(order);

    }

    file.close();

    return true;
}
