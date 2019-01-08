#include "Program.h"
#include "Product.h"
#include "Person.h"
#include "COD_Order.h"
#include "PRE_Order.h"
#include "PER_Order.h"

#include <conio.h>
#include <iostream>
#include <algorithm>
#include <exception>
#include <string>
#include <cstdlib>

using std::cout;
using std::string;


void Program::runProgram()
{
    _database.loadFromFile();
    _currentMenu = Program::mainMenu;

    while (!_isEnd)
    {
        if (_isFindingProduct)
        {
            _findingProductFunction(this, _findingProduct);
        }
        else
        {
            _currentMenu(this);
        }
    }
}


void Program::mainMenu()
{
    _userInterface.showMenu();
    switch (getUserOptionChoice(3))
    {
    case 1:
        _currentMenu = Program::productMenu;
        break;
    case 2:
        _currentMenu = Program::orderMenuOperations;
        break;
    case 3:
        _isEnd = true;
        break;
    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
    }
}

void Program::showActiveOrders()
{
    system("cls");
    showOrderList();
}

void Program::showArchivalOrders()
{
    system("cls");
    _userInterface.showOrderListHeaders();

    std::vector<Order*> archivalOrders = _database.getArchivalOrders();

    std::for_each(archivalOrders.begin(), archivalOrders.end(), [](Order* order) {
        cout << *order;
//        order->showOrder();
    });

    _currentMenu = Program::showOrderListMenuOperations;

}


void Program::productMenu()
{
    _userInterface.showProductMenu();

    switch (getUserOptionChoice(4))
    {
    case 1:
        _currentMenu = Program::showProductList;
        break;
    case 2:
        _currentMenu = Program::addProduct;
        break;
    case 3:
        _currentMenu = Program::findProduct;
        break;
    case 4:
        _currentMenu = Program::mainMenu;
        break;
    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
    }
}

void Program::addProduct()
{
    string name;
    float price;
    system("cls");

    cout << "Podaj nazwe produktu: ";
    name = getStringInput();

    cout << "Podaj cene produktu: ";
    price = getFloatInput();

    if (!_database.addProduct(new Product(name, price)))
    {
        cout << "Produkt o podanej nazwie znajduje sie juz w bazie\n";
        cout << "1. POWROT";

        switch (getUserOptionChoice(1))
        {
        case 1:
            _currentMenu = Program::productMenu;
            break;
        default:
            throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
        }
    }

    _currentMenu = Program::productMenu;
}


void Program::showProductList()
{
    system("cls");
    _userInterface.showProductListHeaders();

    std::vector<Product*> products = _database.getAllProducts();

    std::for_each(products.begin(), products.end(), [](Product* product){
//        product->printInfo();
        // dereferencja, bo używamy product to wskaźnik, a operator oczekuje obiektu, niewskaźnika
        cout << *product;
    });

    cout << "1. POWROT";

    switch (getUserOptionChoice(1))
    {
    case 1:
        _currentMenu = Program::productMenu;
        break;
    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
    }
}


void Program::findProduct()
{
    system("cls");
    cout << "1. WYSZUKAJ PO NAZWIE PRODUKTU\n";
    cout << "2. WYSZUKAJ PO NUMERZE PRODUKTU\n";

    Product *product = nullptr;
    string name;
    int no;

    switch (getUserOptionChoice(2))
    {
    case 1:
        system("cls");
        cout << "Podaj nazwe produktu: ";
        name = getStringInput();

        product = _database.getProduct(name);
        break;
    case 2:
        system("cls");
        cout << "Podaj numer produktu: ";
        no = getIntInput();

        product = _database.getProduct(no);
        break;
    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
    }

    if (product == nullptr)
    {
        system("cls");
        cout << "Nie znaleziono pasujacego produktu\n";
        cout << "1. POWROT";

        switch (getUserOptionChoice(1))
        {
        case 1:
            _currentMenu = Program::productMenu;
            _isFindingProduct = false;
            break;
        default:
            throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
        }

    }
    else
    {
        system("cls");
        _userInterface.showProductListHeaders();
        cout << *product;
//        product->printInfo();

        _isFindingProduct = true;
        _findingProductFunction = Program::findProductMenu;
        _findingProduct = product;
    }
}

void Program::orderMenuOperations()
{
    _userInterface.showOrderMenu();

    switch (getUserOptionChoice(4))
    {
    case 1:
        _currentMenu = Program::showActiveOrders;
        break;
    case 2:
        _currentMenu = Program::showArchivalOrders;
        break;
    case 3:
        _currentMenu = Program::addOrder;
        break;
    case 4:
        _currentMenu = Program::mainMenu;
        break;
    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
    }
}

void Program::addOrder()
{
    system("cls");
    Product product;
    string firstName;
    string lastName;
    int phoneNumber;
    int numberOfProducts;
    int no;
    cout << "Wprowadz dane klienta\n"
         << "Imie: ";
    firstName = getStringInput();

    cout << "Nazwisko: ";
    lastName = getStringInput();

    cout << "Numer telefonu: ";
    phoneNumber = getIntInput();

    Person customer(firstName, lastName, phoneNumber);


    cout << "Wybierz rodzaj dostawy:\n"
         << "1. Przesylka - platnosc przy odbiorze\n"
         << "2. Przesylka - przedplata\n"
         << "3. Odbior osobisty";

    Order* order;

    switch (getUserOptionChoice(3))
    {
    case 1:
        order = new COD_Order(customer);
        break;
    case 2:
        order = new PRE_Order(customer);
        break;
    case 3:
        order = new PER_Order(customer);
        break;
    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
    }

    cout << "\nIle produktow chcesz dodac do zamowienia? ";
    numberOfProducts = getIntInput();

    std::vector<Product*> products = _database.getAllProducts();

    cout << "\nCzy chcesz wyswietlic liste wszystkich produktow?\n"
         << "1. Tak\n"
         << "2. Nie\n";

    switch (getUserOptionChoice(2))
    {
    case 1:
        cout << "\n\n";
        _userInterface.showProductListHeaders();
        std::for_each(products.begin(), products.end(), [](Product* product){
            cout << *product;
//            product->printInfo();
        });
        break;
    case 2:
        break;
    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
    }

    for (int i = 0; i < numberOfProducts; i++)
    {
        cout << "Wprowadz numer " << i + 1 << " produktu: ";
        no = getIntInput();

        product = *products[no - 1];
        order->addItem(product);
    }

    _database.addOrder(order);


    _currentMenu = Program::orderMenuOperations;
}

void Program::showOrderListMenuOperations()
{
    _userInterface.showOrderListMenu();

    switch (getUserOptionChoice(2))
    {
    case 1:
        int no;
        cout << "\nPodaj numer zamowienia ";
        no = getIntInput();
        _database.getOrder(no-1)->showDetails();

        cout << "\n1. PRZENIES DO ARCHIWUM"
             << "\n2. POWROT";

        switch (getUserOptionChoice(2))
        {
        case 1:
            _database.getOrder(no-1)->makeArchival(); /// to nie działa, bo to kopia (?)
            break;
        case 2:
            break;
        default:
            throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
        }

        system("cls");
        _currentMenu = Program::showOrderList;
        break;
    case 2:
        _currentMenu = Program::orderMenuOperations;
        break;
    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
    }
}

void Program::showOrderList()
{
    _userInterface.showOrderListHeaders();

    auto orders = _database.getActiveOrders();
    for(auto order : orders)
    {
        if(order->isActive())
            cout << *order;
//            order->showOrder();
    }

    _currentMenu = Program::showOrderListMenuOperations;
}

void Program::findProductMenu(Product* product)
{   
    _userInterface.showFindProductMenu();

    switch (getUserOptionChoice(3))
    {
    case 1:
        _findingProductFunction = Program::editProduct;
        break;
    case 2:
        _isFindingProduct = false;
        _currentMenu = Program::findProduct;
        break;
    case 3:
        _isFindingProduct = false;
        _currentMenu = Program::productMenu;
        break;
    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");
    }
}

void Program::editProduct(Product *product)
{
    string name;
    float price;

    _userInterface.showEditProductMenu(product);

    switch (getUserOptionChoice(4))
    {
    case 1:
        system("cls");
        cout << "Obecna nazwa: " << product->getName();
        cout << "\nNowa nazwa: ";
        name = getStringInput();

        product->setName(name);
        break;

    case 2:
        system("cls");
        cout << "Obecna cena: " << product->getPrice();
        cout << "\nNowa cena: ";
        price = getFloatInput();

        product->setPrice(price);
        break;

    case 3:
        product->changeAvailability();
        break;

    case 4:
        _currentMenu = Program::productMenu;
        _isFindingProduct = false;
        break;

    default:
        throw std::invalid_argument("getUserOptionChoice - niepoprawna wartosc argumentu");

    }
}

int Program::getUserOptionChoice(int optionsNumber) const
{
    if (optionsNumber < 1)
        return -1;

    char input;
    const char baseOption = '1';
    bool isInputValid = false;

    while (!isInputValid)
    {
        input = _getch();

        for (int i = 0; i < optionsNumber; ++i)
        {
            if (input == baseOption + i)
            {
                isInputValid = true;
            }
        }
    }

    // lambda, która zamienia char na int
    // moglbym napisac:
    // return input - '0';
    // ale wtedy nie od razu wiadomo o co chodzi. a tak nazwa funkcji mowi co sie dzieje
    // i użylem lambdy, bo nie ma sensu tworzyć zwykłej funkcji, żeby użyć jej tylko w jednym miejscu
    auto charToInt = [](char value) ->int { return (value - '0'); };

    return charToInt(input);
}

std::string Program::getStringInput() const
{
    std::string input;
    std::getline(std::cin, input);

    return input;
}

int Program::getIntInput() const
{
    int input;
    bool isValid;
    do
    {
        isValid =  true;
        try
        {
            input = std::stoi(getStringInput());
        }
        catch (...)
        {
            cout << "Niepoprawne dane! Sprobuj ponownie: \n";
            isValid = false;
        }
    }
    while (!isValid);

    return input;
}

float Program::getFloatInput() const
{
    float input;
    bool isValid;
    do
    {
        isValid =  true;
        input = atof(getStringInput().c_str());

        if (input <= 0.0f)
            isValid = false;

    }
    while (!isValid);

    return input;
}



///INTERFACE
void Program::UserInterface::showMenu() const
{
    system("cls");
    cout << "1. PRODUKTY\n"
         << "2. ZAMOWIENIA\n"
         << "3. KONIEC\n";
}


void Program::UserInterface::showProductListHeaders()
{
    cout.width(8);
    cout << "Numer";
    cout.width(20);
    cout << "Nazwa produktu";
    cout.width(10);
    cout << "Cena";
    cout.width(15);
    cout << "Dostepnosc\n";
}

void Program::UserInterface::showOrderListHeaders() const
{
    cout.width(10);
    cout << "Numer";
    cout.width(10);
    cout << "Nazwa";
    cout.width(20);
    cout << "Imie";
    cout.width(20);
    cout << "Nazwisko";
    cout.width(10);
    cout << "Wartosc\n";
}


void Program::UserInterface::showProductMenu() const
{
    system("cls");
    cout << "1. LISTA PRODUKTOW\n"
         << "2. DODAJ PRODUKT\n"
         << "3. WYSZUKAJ PRODUKT\n"
         << "4. POWROT DO MENU\n";
}

void Program::UserInterface::showOrderMenu() const
{
    system("cls");
    cout << "1. AKTYWNE ZAMOWIENIA\n"
         << "2. ARCHIWALNE ZAMOWIENIA\n"
         << "3. DODAJ ZAMOWIENIE\n"
         << "4. POWROT DO MENU\n";
}

void Program::UserInterface::showPersonHeaders() const
{

    cout.width(20);
    cout << "Imie";
    cout.width(20);
    cout << "Nazwisko";
    cout.width(15);
    cout << "Numer telefonu\n";
}

void Program::UserInterface::showEditProductMenu(Product * const product) const
{
    system("cls");
    cout << "1. EDYTUJ NAZWE\n";
    cout << "2. EDYTUJ CENE\n";
    if (product->getAvailability() == true)
    {
        cout << "3. OZNACZ JAKO NIEDOSTEPNY\n";
    }
    else
    {
        cout << "3. OZNACZ JAKO DOSTEPNY\n";
    }
    cout << "4. POWROT";
}

void Program::UserInterface::showOrderListMenu() const
{
    cout << "\n\n1. WYSWIETL SZCZEGOLY WYBRANEGO ZAMOWIENIA"
         << "\n2. POWROT";
}

void Program::UserInterface::showFindProductMenu() const
{
    cout << "1. EDYTUJ PRODUKT\n";
    cout << "2. WYSZUKAJ KOLEJNY PRODUKT\n";
    cout << "3. POWROT\n";
}
