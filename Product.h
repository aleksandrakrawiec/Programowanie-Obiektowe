#pragma once
#include <iostream>
#include <string>

using std::string;

class Product
{
public:
    class CompareByName
    {
    public:
        CompareByName(const string& name) : _name(name) {}
        bool operator()(Product* product) const
        {
            return (product->getName() == _name);
        }

    private:
        string _name;
    };

    class CompareByNumber
    {
    public:
        CompareByNumber(int number) : _number(number) {}
        bool operator()(Product* product) const
        {
            return (product->getNo() == _number);
        }

    private:
        int _number;
    };

    Product();
    Product(const string& name, float price, bool availability = true);

    string getName() const;
    float getPrice() const;
    int getNo() const;
    bool getAvailability() const;
    void setName(const string& name);
	void setPrice(float price);
	void changeAvailability();
    void printInfo() const;
    static void increaseProductsAmount();

    friend std::ostream& operator<< (std::ostream& stream, const Product& product);

    Product& operator<< (const std::string& name);
    Product& operator<< (float price);
    Product& operator<< (bool availability);

    Product& operator>> (std::string& name);
    Product& operator>> (float& price);
    Product& operator>> (bool& availability);

private:
    static int _amount;

    int _no;
    string _name;
    float _price;
    bool _availability;

};


