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

Person::~Person()
{
}

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
	cout.width(20);
	cout << _firstName;
	cout.width(20);
	cout << _lastName;
	cout.width(15);
	cout << _phoneNumber << "\n";
}

std::ostream& operator<<(std::ostream& stream, const Person& person)
{
    stream.width(20);
    stream << person._firstName;

    stream.width(20);
    stream << person._lastName;

    stream.width(15);
    stream << person._phoneNumber << "\n";

    return stream;
}
