#include "Order.h"
#include "Database.h"
#include <vector>
#include <functional>


class Program
{    
	void showActiveOrders();
	void showArchivalOrders();
    void mainMenu();
    void productMenu();
	void addProduct();
	void showProductList();
	void findProduct();
	void orderMenuOperations();
	void addOrder();
	void showOrderList();
	void showOrderListMenuOperations();
    void findProductMenu(Product *product);
	void editProduct(Product *product);

    int getUserOptionChoice(int optionsNumber) const;

public:
    Database database;

	void runProgram();

	class UserInterface
	{
	public:
		void showMenu();
		void showProductMenu();
		void showOrderMenu();
		void showOrderListMenu();
        void showFindProductMenu();
		static void showProductListHeaders();
        static void showOrderListHeaders();
		void showPersonHeaders();
        void showEditProductMenu(Product* const product);
	};

private:
	UserInterface userInterface;
    std::function<void(Program*)> _currentMenu;
    std::function<void(Program*, Product*)> _findingProductFunction;
    bool _isEnd = false;
    bool _isFindingProduct = false;

    Product* _findingProduct = nullptr;
};
