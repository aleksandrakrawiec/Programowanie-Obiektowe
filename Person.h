#pragma once

#include <iostream>
#include <string>

using std::string;

class Person
{
public:
    Person();
    Person(string firstName, string lastName, int phoneNumber);

	string getFirstName() const;
	string getLastName() const;
    int getPhoneNumber() const;
    void showPerson() const;

    friend std::ostream& operator<<(std::ostream& stream, const Person& person);

private:
    string _firstName;
    string _lastName;
    int _phoneNumber;
};
