#include "Order.h"
#include "Database.h"
#include "DeliveryOrder.h"
#include <vector>
#include <functional>


class Program
{
public:
    class UserInterface
    {
    public:
        static void showProductListHeaders();

        void showMenu() const;
        void showProductMenu() const;
        void showOrderMenu() const;
        void showOrderListHeaders() const;
        void showOrderListMenu() const;
        void showFindProductMenu() const;
        void showPersonHeaders() const;
        void showEditProductMenu(Product* const product) const;
    };


    void runProgram();

private:
    Database _database;
    UserInterface _userInterface;

    std::function<void(Program*)> _currentMenu;
    std::function<void(Program*, Product*)> _findingProductFunction;

    bool _isEnd = false;
    bool _isFindingProduct = false;
    Product* _findingProduct = nullptr;

    void showActiveOrders();
    void showArchivalOrders();
    void mainMenu();
    void productMenu();
    void addProduct();
    void showProductList();
    void findProduct();
    void orderMenuOperations();
    DeliveryOrder::DeliveryAddress addAddress();
    void addOrder();
    void showOrderList();
    void showOrderListMenuOperations();
    void showArchivalOrdersOperations();
    void findProductMenu(Product *product);
    void editProduct(Product *product);

    int getUserOptionChoice(int optionsNumber) const;
    std::string getStringInput() const;
    int getIntInput() const;
    float getFloatInput() const;
};
