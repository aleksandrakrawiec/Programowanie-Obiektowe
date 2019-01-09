#include "Person.h"


using std::cout;
using std::string;


Person::Person()
{

}

Person::Person(string firstName, string lastName, int phoneNumber) :
	_firstName(firstName),
	_lastName(lastName),
	_phoneNumber(phoneNumber) {}

string Person::getFirstName() const
{
	return _firstName;
}

string Person::getLastName() const
{
	return _lastName;
}

int Person::getPhoneNumber() const
{
	return _phoneNumber;
}

void Person::showPerson() const
{
    std::cout << "Imie: " << _firstName
         << "\nNazwisko: " << _lastName
         << "\nNumer telefonu: " << _phoneNumber;
}

std::ostream& operator<<(std::ostream& stream, const Person& person)
{
    stream << person._firstName;
    stream << person._lastName;
    stream << person._phoneNumber;

    return stream;
}
