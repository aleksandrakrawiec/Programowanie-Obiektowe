#pragma once
#include <iostream>
#include <string>

using std::string;

class Product
{
	string _name;
	float _price;
	int _no;
	bool _availability;

public:
    static int _amount;
	Product();
	Product(string name, float price);
    string getName();
    float getPrice();
    int getNo();
	bool getAvailability();
	void setName(string name);
	void setPrice(float price);
	void changeAvailability();
    void printInfo();

    friend std::ostream& operator<< (std::ostream& stream, const Product& product);

    Product& operator<< (const std::string& name);
    Product& operator<< (float price);
    Product& operator<< (bool availability);

    Product& operator>> (std::string& name);
    Product& operator>> (float& price);
    Product& operator>> (bool& availability);

//    virtual void printDetailedInfo() = 0;
};


