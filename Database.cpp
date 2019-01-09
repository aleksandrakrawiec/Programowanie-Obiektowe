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

    // write data of all products
    for (const auto& product : _products)
    {
        string name;
        float price;
        bool availability;

        // extract product data using overloaded >> operator
        *product >> name >> price >> availability;

        // write it to file
        file << name << std::endl;
        file << price << std::endl;
        file << availability << std::endl; // bool implicitly casts to int, so value will be 0 or 1
    }

    // write orders count
    file << _orders.size() << std::endl;

    // write data of all orders
    for (auto order : _orders)
    {
        // we need a way to define exact order type, i.e. is it COD_Order, PER_Order or PRE_Order
        // it can be done in that way:
        // POL: musimy zapisać jakiego dokładnie typu jest zamówienie, tzn czy to COD_Order itp

        // we try to cast order to COD_Order. if that particular order is really pointing to COD_Order, then pointer we created is not nullptr
        // POL: próbujemy zrzutować nasze zamówienie na typ COD_Order. jeżeli to się powiedzie, to nasza zmienna cod_order nie bedzie nullptr.
        // jeżeli order nie będzie typu COD_Order, to cod_order bedzie nullptrem.
        // jeżeli jedno rzutowanie się powiedzie, to na pewno inne sie nie powiodą, więc można zapisać to tak jak niżej

//        COD_Order* cod_order = dynamic_cast<COD_Order*>(order);
//        if (cod_order != nullptr)
//            file << 0 << std::endl; // let 0 means COD_Order type

//        PRE_Order* pre_order = dynamic_cast<PRE_Order*>(order);
//        if (pre_order != nullptr)
//            file << 1 << std::endl;

//        PER_Order* per_order = dynamic_cast<PER_Order*>(order);
//        if (per_order != nullptr)
//            file << 2 << std::endl;


        // znalazłem troche lepszy sposób, ale to wyżej też możesz przeanalizować
        // kod mowi sam za siebie
        // typeid działa po dodaniu headera <typeinfo>
        if (typeid(*order) == typeid(COD_Order))
            file << COD_OrderType << std::endl; // it gonna write '0'

        else if (typeid(*order) == typeid(PRE_Order)) // it gonna write '1' ect..
            file << PRE_OrderType << std::endl;

        else if (typeid(*order) == typeid(PER_Order))
            file << PER_OrderType << std::endl;

        else
            return false;

        Person customer;
        string name;
        bool active;

        // extract order 'single' data
        *order >> customer >> name >> active;

        // write it to file
        file << customer << std::endl;
        file << name << std::endl;
        file << active << std::endl;

        // write count of products for particular order
        int productsCount = order->getProductsCount();
        file << productsCount << std::endl;

        for (int i = 0; i < productsCount; ++i)
        {
            // get product number from order using overloaded [] opeartor
            // order must be dereferenced first, because it is a pointer, to use operator[] you need an object
            // brackets are neccessary, *order[i] doesn't work

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

    // something went wrong, return false
    if (!file.is_open())
        return false;

    // check is file empty
    file.seekg(0, file.end);
    if (file.tellg() == 0)
        return true;

    file.seekg(0, file.beg);

    // clear all products
    _products.clear();
    _orders.clear();

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
        // rzutujemy int na enuma, co jest ok
        OrderType orderType = static_cast<OrderType>(std::stoi(input));

        std::getline(file, input);
        string customerFirstName = input;

        std::getline(file, input);
        string customerLastName = input;

        std::getline(file, input);
        int customerPhoneNumber = std::stoi(input);

        std::getline(file, input);
        string name = input;

//        std::getline(file, input);
//        float value = atof(input.c_str());

        std::getline(file, input);
        // rzutujemy int na boola, tez spoko
        bool active = static_cast<bool>(std::stoi(input));

        Person customer(customerFirstName, customerLastName, customerPhoneNumber);

        Order* order;

        switch (orderType)
        {
        case COD_OrderType:
            order = new COD_Order(customer);
            break;
        case PRE_OrderType:
            order = new PRE_Order(customer);
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
