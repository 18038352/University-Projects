#include <iostream>
#include <string>
#include<fstream>
#include<stdio.h>//for remove( ) and rename( )

enum SERVICE { BASIC_DELIVERY, EXPRESS_DELIVERY, PICKUP_ITEM}; // enumeration named SERVICE, with the values of BASIC_DELIVERY, EXPRESS_DELIVERY, and PICKUP_ITEM Of type Service.

using namespace std;


//User selects what Outlet they want to buy from
class Outlet
{
public:
	int selectOutlet; //var (variable) of type int for selection of outlet
	void selectingOutlet()//method for selecting outlet
	{
	
		//Prints Selection of Outlets to the screen, which users can choose from

	do //do while loop to keep looping options below unless one of the 4 options are selected
	{
		cout << "-------------------------------------Select Outlet---------------------------------------" << endl;
		cout << "1.) Cardiff, 2.) Pontypridd, 3.) Treforest, 4.) Exit" << endl;
		cin >> selectOutlet;

		if (selectOutlet == 1) //if user input is 1 this outlet is selected
		{
			cout << "Selected Cardiff" << endl;

		}

		else if (selectOutlet == 2) //if user input is 2 this outlet is selected
		{
			cout << "Selected Pontypridd" << endl;

		}

		else if (selectOutlet == 3) ////if user input is 3 this outlet is selected
		{
			cout << "Selected Treforest" << endl;

		}

		else if (selectOutlet == 4) //if user input is 4, exit program
		{
			cout << "Exiting..." << endl;
			exit(1);//exits console

		}

		else
		{
			cout << "Incorrect Input, please try again" << endl;// other number inputs will be incorrect which loops back user to the start of browse item
		}
	} while (selectOutlet != 1 && selectOutlet != 2 && selectOutlet != 3); //while not equal 1, 2, 3 keep looping outlet options
	}
};

//Home Screen Class (enable users to access features of the app)
class Home
{
public:
	void displayOptions() // displays features of the app that users can choose from, and access these screens
	{
		bool repeat = true; //var of type bool set to true, to repeat/return back to home screen after accessing selections below
		int selectOption; //var of type int, used for if statements for users to select/access features of app
		while (repeat = true)
		{
			cout << "----------------------------------------Welcome to Mend-it Hardware Outlet--------------------------------------------" << endl;
			cout << "Select an option from below" << endl;
			cout << "1.) Browse Items" << endl;
			cout << "2.) Browse Accessories" << endl;
			cout << "3.) View Order (Cancel/Keep Order)" << endl;
			cout << "4.) Pay for order" << endl;
			cout << "5.) Exit" << endl;
			cin >> selectOption; //user input for selection

			if (selectOption == 1)
			{
				cout << "Browsing Item" << endl;
				ViewItems();//users access item browsing method 

			}

			else if (selectOption == 2)
			{
				cout << "Browse Accessories" << endl;

			}

			else if (selectOption == 3)
			{
				cout << "Viewing Orders" << endl;
				ViewOrders();//access method to cancel or keep order


			}

			else if (selectOption == 4)
			{
				cout << "Pay for order" << endl;


			}

			else if (selectOption == 5)
			{
				cout << "Exiting..." << endl;
				exit(1);//exit console

			}

			else
			{
				cout << "Incorrect Input, please try again" << endl;
			}
		}
	}

	void ViewItems(); //method to browse, pay, and order items and accessories. 
	void ViewOrders(); //method to show completed orders, allowing users to cancel or keep order.
};


//base class
class Item 
{
public:
	Item() //default constructor
	{
		//if class did not work properly output message below, along with setting pickup service as default choice
		this->itemName = "Unknown Item";
		service = PICKUP_ITEM;
		
	}

	int getService() { //new function added based on the realisation of Item with accessories
		return service;
	}

	void setService(int serviceOfItem) //customer can chose different types of service for their orders
	{

		switch (serviceOfItem)
		{
		case BASIC_DELIVERY:
			service = BASIC_DELIVERY; //Enter 0 for Basic Delivery
			break;
		case EXPRESS_DELIVERY:
			service = EXPRESS_DELIVERY; // Enter 1 for Express Delivery
			break;
		case PICKUP_ITEM:
		default:
			service = PICKUP_ITEM; // Enter 2 or any number for pick-up order
			break;
		}
	}
	virtual string getItemName() = 0; //implemented differently by every class that inherits Item, allows to set different names for items/accessories, gets item/accessories name of all the classes of items/accessories, which is set to zero here.
	virtual double cost() = 0; //implemented differently by every class that inherits Item, allows cost of items and accessories to have different costs in their classes, currently set to zero
protected:
	string itemName; // var of type string used to name items and accessories

private:
	SERVICE service; // declaring a variable of type SERVICE, used to set types of service for items and accessories in the program
};

//decoration, abstract decoration (abstract class every accessory that is added will be implemented differently)
class AccessoriesDecorator:public Item
{
public:
	virtual string getItemName() = 0; //implemented in inherited class

};

//Specific main Item, inherited from super class, specific component
class Paint : public Item
{
public:
	Paint()//constructor
	{
		itemName = "Paint"; //sets itemName to Paint
	}
	double cost() // method that calculates the cost of item with service cost included.
	{
		double overallCost; //var of type double to store overall cost of item and service
		switch (getService())//switch to choose from what service user wants for the item, which has different prices depedning on service type, has item price added.
		{
		case BASIC_DELIVERY:
			overallCost = 8.00;
			break;
		case EXPRESS_DELIVERY:
			overallCost = 9.00; 
			break;
		case PICKUP_ITEM:
		default:
			overallCost = 5.50;//price of item without service cost
			break;
		}
		return overallCost; // returns the cost of item and service
	}

	string getItemName()//method that returns itemName
	{
		return itemName;
	}
};

class Notebook : public Item
{
public:
	Notebook()
	{
		itemName = "Notebook"; //sets itemName to Notebook
	}
	double cost() // method that calculates the cost of item with service cost included.
	{
		double overallCost; //var of type double to store overall cost of item and service
		switch (getService())//switch to choose from what service user wants for the item, which has different prices depedning on service type, has item price added.
		{
		case BASIC_DELIVERY:
			overallCost = 7.00;
			break;
		case EXPRESS_DELIVERY:
			overallCost = 8.00;
			break;
		case PICKUP_ITEM:
		default:
			overallCost = 4.50;
			break;
		}
		return overallCost; // returns the cost of item and service
	}

	string getItemName() //method that returns itemName
	{
		return itemName;
	}
};

class Wallpaper : public Item
{
public:
	Wallpaper()
	{
		itemName = "Wallpaper"; //sets itemName to Wallpaper
	}
	double cost()// method that calculates the cost of item with service cost included.
	{
		double overallCost;  //var of type double to store overall cost of item and service
		switch (getService())//switch to choose from what service user wants for the item, which has different prices depedning on service type, has item price added.
		{
		case BASIC_DELIVERY:
			overallCost = 8.00;
			break;
		case EXPRESS_DELIVERY:
			overallCost = 9.00;
			break;
		case PICKUP_ITEM:
		default:
			overallCost = 5.50;
			break;
		}
		return overallCost;  // returns the cost of item and service
	}

	string getItemName() //method that returns itemName
	{
		return itemName;
	}
};


//item with zero values, used when user inputs an item number that is not in the options, so no item, service, or cost is added when incorrect input takes place
class NoItem : public Item
{
public:
	NoItem()
	{
		itemName = "No Item"; //sets itemName to No Item
	}
	double cost()// method that calculates the cost of item with service cost included.
	{
		double overallCost;//var of type double to store overall cost of item and service
		switch (getService())//switch to choose from what service user wants for the item, which has different prices depedning on service type, has item price added.
		{
		case BASIC_DELIVERY:
			overallCost = 0;
			break;
		case EXPRESS_DELIVERY:
			overallCost = 0;
			break;
		case PICKUP_ITEM:
		default:
			overallCost = 0;
			break;
		}
		return overallCost;// returns the cost of item and service
	}

	string getItemName()//method that returns itemName
	{
		return itemName;
	}
};

//Decorators classes, accessories classes
//Accessories, specific decoration
//specific decorator, inherited from super class, specific component
class Brush: public AccessoriesDecorator 
{
private:
	Item* _item;//creating object of type Item
public:
	Brush(Item* item) //constructor, setting _item to item
	{
		_item = item;
	}
	string getItemName()// method that gets name of item and accessory
	{
		return _item->getItemName() + ", Brush"; 
	}

	double cost()//method that calculates overall costs of item, accessory, and service.
	{
		double overallCost = _item->cost(); //sets overallcost to base cost + everything wrapped around it (accessory cost)
		switch (getService())
		{
		case BASIC_DELIVERY:
			overallCost += 5.00;//overallcost = item cost + accessory cost and service cost.
			break;
		case EXPRESS_DELIVERY:
			overallCost += 6.00;
			break;
		case PICKUP_ITEM:
		default:
			overallCost += 2.50;
			break;
		}
		return overallCost;
	}
};

class Roller : public AccessoriesDecorator
{
private:
	Item* _item; //creating object of type Item
public:
	Roller(Item* item) //constructor, setting _item to item
	{
		_item = item;
	}
	string getItemName() // method that gets name of item and accessory
	{
		return _item->getItemName() + ", Roller";
	}

	double cost() //method that calculates overall costs of item, accessory, and service.
	{
		double overallCost = _item->cost(); //sets overallcost to base cost + everything wrapped around it (accessory cost)
		switch (getService())
		{
		case BASIC_DELIVERY:
			overallCost += 4.00; //overallcost = item cost + accessory cost and service cost.
			break;
		case EXPRESS_DELIVERY:
			overallCost += 5.00;
			break;
		case PICKUP_ITEM:
		default:
			overallCost += 1.50;
			break;
		}
		return overallCost;
	}
};

class Tape : public AccessoriesDecorator
{
private:
	Item* _item;//creating object of type Item
public:
	Tape(Item* item) //constructor, setting _item to item
	{
		_item = item;
	}
	string getItemName() // method that gets name of item and accessory
	{
		return _item->getItemName() + ", Tape";
	}

	double cost() //method that calculates overall costs of item, accessory, and service.
	{
		double overallCost = _item->cost();//sets overallcost to base cost + everything wrapped around it (accessory cost)
		switch (getService())
		{
		case BASIC_DELIVERY:
			overallCost += 4.00;  //overallcost = item cost + accessory cost and service cost.
			break;
		case EXPRESS_DELIVERY:
			overallCost += 5.00;
			break;
		case PICKUP_ITEM:
		default:
			overallCost += 1.50;
			break;
		}
		return overallCost;
	}
};

class Pen : public AccessoriesDecorator
{
private:
	Item* _item;//creating object of type Item
public:
	Pen(Item* item) //constructor, setting _item to item
	{
		_item = item;
	}
	string getItemName() // method that gets name of item and accessory
	{
		return _item->getItemName() + ", Pen";
	}

	double cost() //method that calculates overall costs of item, accessory, and service.
	{
		double overallCost = _item->cost(); //sets overallcost to base cost + everything wrapped around it (accessory cost)
		switch (getService())
		{
		case BASIC_DELIVERY:
			overallCost += 3.00;  //overallcost = item cost + accessory cost and service cost.
			break;
		case EXPRESS_DELIVERY:
			overallCost += 4.00;
			break;
		case PICKUP_ITEM:
		default:
			overallCost += 0.50;
			break;
		}
		return overallCost;
	}



};

class Pencil : public AccessoriesDecorator
{
private:
	Item* _item; //creating object of type Item
public:
	Pencil(Item* item) //constructor, setting _item to item
	{
		_item = item;
	}
	string getItemName() // method that gets name of item and accessory
	{
		return _item->getItemName() + ", Pencil";
	}

	double cost()//method that calculates overall costs of item, accessory, and service.
	{
		double overallCost = _item->cost(); //sets overallcost to base cost + everything wrapped around it (accessory cost)
		switch (getService())
		{
		case BASIC_DELIVERY:
			overallCost += 3.00;  //overallcost = item cost + accessory cost and service cost.
			break;
		case EXPRESS_DELIVERY:
			overallCost += 4.00;
			break;
		case PICKUP_ITEM:
		default:
			overallCost += 0.50;
			break;
		}
		return overallCost;
	}
};

class Eraser : public AccessoriesDecorator
{
private:
	Item* _item;//creating object of type Item
public:
	Eraser(Item* item)//constructor, setting _item to item
	{
		_item = item;
	}
	string getItemName()// method that gets name of item and accessory
	{
		return _item->getItemName() + ", Eraser";
	}

	double cost()//method that calculates overall costs of item, accessory, and service.
	{
		double overallCost = _item->cost(); //sets overallcost to base cost + everything wrapped around it (accessory cost)
		switch (getService())
		{
		case BASIC_DELIVERY:
			overallCost += 3.00;  //overallcost = item cost + accessory cost and service cost.
			break;
		case EXPRESS_DELIVERY:
			overallCost += 4.00;
			break;
		case PICKUP_ITEM:
		default:
			overallCost += 0.50;
			break;
		}
		return overallCost;
	}
};

class Glue : public AccessoriesDecorator
{
private:
	Item* _item;//creating object of type Item
public:
	Glue(Item* item)//constructor, setting _item to item
	{
		_item = item;
	}
	string getItemName()// method that gets name of item and accessory
	{
		return _item->getItemName() + ", Glue";
	}

	double cost()//method that calculates overall costs of item, accessory, and service.
	{
		double overallCost = _item->cost(); //sets overallcost to base cost + everything wrapped around it (accessory cost)
		switch (getService())
		{
		case BASIC_DELIVERY:
			overallCost += 4.00;  //overallcost = item cost + accessory cost and service cost.
			break;
		case EXPRESS_DELIVERY:
			overallCost += 5.00;
			break;
		case PICKUP_ITEM:
		default:
			overallCost += 1.50;
			break;
		}
		return overallCost;
	}
};

class Scissors : public AccessoriesDecorator
{
private:
	Item* _item;//creating object of type Item
public:
	Scissors(Item* item)//constructor, setting _item to item
	{
		_item = item;
	}
	string getItemName()// method that gets name of item and accessory
	{
		return _item->getItemName() + ", Scissors";
	}

	double cost()//method that calculates overall costs of item, accessory, and service.
	{
		double overallCost = _item->cost(); //sets overallcost to base cost + everything wrapped around it (accessory cost)
		switch (getService())
		{
		case BASIC_DELIVERY:
			overallCost += 5.00;  //overallcost = item cost + accessory cost and service cost.
			break;
		case EXPRESS_DELIVERY:
			overallCost += 6.00;
			break;
		case PICKUP_ITEM:
		default:
			overallCost += 2.50;
			break;
		}
		return overallCost;
	}
};

//Writes and reads oders of customers to file (Invoice)
class Invoice
{

private:
	
	ofstream outputfile; //create and write files (Invoice).

public:

	string filename;//var of type string to store phoneNum of customer, used to write customers phonenum as file name (invoice)
	void WriteInvoiceToFile(string firstname, string surname, string homeAddress, string phoneNum, string itemsOrdered, int service_type, int outlet_choice, double totalPrice)//method which writes/stores order details and customer details. These variables in parameter are later on assigned with variables that holds data to store in file
	{
		filename = phoneNum; //setting filename to phone number to use customer's phone numbers as filename 
		outputfile.open(filename + ".txt"); //open and creating file, naming it with customer's phonenum (e.g. 07882345432.txt)
		outputfile << "-------------------------------------Order Details---------------------------------------" << endl;//below sets the format/layout of lines of data in the file
		outputfile << "First name: " << firstname << endl;
		outputfile << "Surname: " << surname << endl;
		outputfile << "Address you want your order to be delivered to: " << homeAddress << endl;
		outputfile << "Phone Number: " << phoneNum << endl;
		outputfile << "Items ordered: " << itemsOrdered << endl;
		outputfile << "Ordered from outlet (1 = Cardiff, 2 = Pontypridd, 3 = Treforest) : " << outlet_choice << endl;
		outputfile << "Service type (0=Basic Delivery (Up to 7 days), 1=Express Delivery (1-2 days), 2=Pickup Delivery): " << service_type << endl;
		if (service_type == 2) //if service choice is pickup, print outlet to pickup order
		{
			outputfile << "Pick-up order in outlet (1=Cardiff, 2=Pontypridd, 3=Treforest): " << outlet_choice << endl;
		}

		else if (service_type == 1) //writes and prints delivery type of order
		{
			outputfile << "Express Delivery was chosen for this order" << endl;
		}

		else if (service_type == 0) //writes and prints delivery type of order
		{
			outputfile << "Basic Delivery was chosen for this order" << endl;
		}
		outputfile << "Total cost of order: $" << totalPrice << endl;
		outputfile.close(); //close file 
	}
	void ReadInvoiceFromFile()//method to read files (customer invoice)
	{
		ifstream inputfile; //read already created files.
		string ReadInvoice;// var of type string used to loop through data in file line by line, untill all lines are printed/read in the console
		cout << "Enter Phone Number used for order: " << endl; //ask user for phone number
		cin >> filename; //user input phone number (filename was set to phoneNum) to find order
		cin.ignore();
		inputfile.open(filename + ".txt"); //opens customer invoice (file) via user's phone number input ((e.g. 07882345432.txt)
		if (!inputfile.is_open())//verify if the file is open, if filename is not found and opened then output message below
		{
			
			cout << "Empty... No order has been made" << endl; //output message
			
		}

		else //if filename (phoneNum.txt) is found and opened
		{

			for (int i{ 0 }; i < 10; i++)  //loop through all the lines in the file to print all data 
			{
				
				
				getline(inputfile, ReadInvoice); //get lines in file, using var readinvoice to loop through lines
				cout << ReadInvoice << endl; //then prints lines out to console 
			}

			inputfile.close(); //close file

			//Below shows the method of deleting an order/invoice/file.
			filename = filename + ".txt"; //setting filename to filename.txt, to find Invoice/order file, e.g. 07449453720.txt (phoneNum.txt).
			int cancelOrder; //var of type int used for user input to cancel or keep order
			cout << "Would you like to cancel or confirm order? (0 to Cancel, 1 to Keep order): " << endl; //message asking to cancel or keep order
			cin >> cancelOrder; 
			if (cancelOrder == 0) //if user input is 0
			{
				remove(filename.c_str()); //remove/delete file that matches phoneNumber that user input
				cout << "Order cancelled" << endl; //which then prints out this message below
			}
			else //else do nothing to keep order then print message below
			{
				cout << "Keeping Order... Order is on its way" << endl;
			}
				
		}


		cin.get();
		
	}

	
};

//method to browse, pay, and order items and accessories
void Home::ViewItems()
{
	Outlet outlet; //create object of type Outlet
	outlet.selectingOutlet();//access outlet selection method from Outlet class to get user to select an outlet


	int service_choice, item_choice, accessory_choice; //variables of type int to get users input for items, service/delivery type, and accessory choice.
	Item* item1; //object of type Item, base on the item type it is then instantiated
	string first_name, customer_surname, delivery_address, phone_number;//variables of type string to store customer details for Order Invoice
	Invoice invoice; //object of type Invoice
	cout << "-------------------------------------Select Item Below---------------------------------------" << endl; //Main items option for user to choose from
	cout << "Enter your Choice of Item:\n"
		<< "1 - Paint\n"
		<< "2 - Notebook\n"
		<< "3 - Wallpaper\n";
	cin >> item_choice;

	switch (item_choice)//switch for users to choose items, 1 = Paint, 2 = Notebook, 3 = Wallpaper.
	{
	case 1:
		item1 = new Paint(); //sets item1 to Paint which gets the itemName and cost (item and service cost) of Paint.
		//Items that are inherited from Item class do not accept parameters within constructors, as this is how base is created, decorator (accessories) is then wrapped around it when choosing accessories for items
		break;
	case 2:
		item1 = new Notebook();//sets item1 to Notebook which gets the itemName and cost (item and service cost) of Notebook.
		break;
	case 3:
		item1 = new Wallpaper(); //sets item1 to Wallpaper which gets the itemName and cost (item and service cost) of Wallpaper.
		break;
	default://when user input is non of the numbers above, NoItem is selected so no items and cost is added, so user will need to try again
		cout << "Invalid choice.\n";
		cout << "No Item was added... Please try again\n";
		item1 = new NoItem();  ////sets item1 to NoItem which gets the itemName and cost (item and service cost) of NoItem..
		break;
	}
	cout << "-------------------------------------Select Accessories---------------------------------------" << endl;
	if (item_choice == 1) //if item Paint is selected ask users if they want its 3 accessories 
	{
		cout << "Would you like to add a Brush?\n"
			<< "1 - Yes\n"
			<< "2 - No\n";
		cin >> accessory_choice;
		switch (accessory_choice)
		{
		case 1:
			item1 = new Brush(item1); //Accessory is added with main item, which gets accessory name and cost, which adds up overallcost of accessory, service/delivery, and main item (everytime object is wrapped with the decorator, cost is incremented).
			//pass the same object as paramater so the properties get wrapped around this object
			break;
		case 2:
			break;
		default: //in default no accessory will be added, no item name and cost.
			cout << "Invalid choice.\n";
			break;
		}

		cout << "Would you like to add a Roller?\n"
			<< "1 - Yes\n"
			<< "2 - No\n";
		cin >> accessory_choice;
		switch (accessory_choice)
		{
		case 1:
			item1 = new Roller(item1);//Accessory is added with main item, which gets accessory name and cost, which adds up overallcost of accessory, service/delivery, and main item (everytime object is wrapped with the decorator, cost is incremented).
			//pass the same object as paramater so the properties get wrapped around this object
			break;
		case 2:
			break;
		default://in default no accessory will be added, no item name and cost.
			cout << "Invalid choice.\n";
			break;
		}

		cout << "Would you like to add a Tape?\n"
			<< "1 - Yes\n"
			<< "2 - No\n";
		cin >> accessory_choice;
		switch (accessory_choice)
		{
		case 1:
			item1 = new Tape(item1);//Accessory is added with main item, which gets accessory name and cost, which adds up overallcost of accessory, service/delivery, and main item (everytime object is wrapped with the decorator, cost is incremented).
			//pass the same object as paramater so the properties get wrapped around this object
			break;
		case 2:
			break;
		default://in default no accessory will be added, no item name and cost.
			cout << "Invalid choice.\n";
			break;
		}
	}

	else if (item_choice == 2) //if item Notebook is selected ask users if they want its 3 accessories 
	{
		cout << "Would you like add a Pen?\n"
			<< "1 - Yes\n"
			<< "2 - No\n";
		cin >> accessory_choice;
		switch (accessory_choice)
		{
		case 1:
			item1 = new Pen(item1);//Accessory is added with main item, which gets accessory name and cost, which adds up overallcost of accessory, service/delivery, and main item (everytime object is wrapped with the decorator, cost is incremented).
			//pass the same object as paramater so the properties get wrapped around this object
			break;
		case 2:
			break;
		default://in default no accessory will be added, no item name and cost.
			cout << "Invalid choice.\n";
			break;
		}

		cout << "Would you like add a Pencil?\n"
			<< "1 - Yes\n"
			<< "2 - No\n";
		cin >> accessory_choice;
		switch (accessory_choice)
		{
		case 1:
			item1 = new Pencil(item1);//Accessory is added with main item, which gets accessory name and cost, which adds up overallcost of accessory, service/delivery, and main item (everytime object is wrapped with the decorator, cost is incremented).
			//pass the same object as paramater so the properties get wrapped around this object
			break;
		case 2:
			break;
		default://in default no accessory will be added, no item name and cost.
			cout << "Invalid choice.\n";
			break;
		}

		cout << "Would you like add a Eraser?\n"
			<< "1 - Yes\n"
			<< "2 - No\n";
		cin >> accessory_choice;
		switch (accessory_choice)
		{
		case 1:
			item1 = new Eraser(item1);//Accessory is added with main item, which gets accessory name and cost, which adds up overallcost of accessory, service/delivery, and main item (everytime object is wrapped with the decorator, cost is incremented).
			//pass the same object as paramater so the properties get wrapped around this object
			break;
		case 2:
			break;
		default://in default no accessory will be added, no item name and cost.
			cout << "Invalid choice.\n";
			break;
		}
	}

	else if (item_choice == 3) //if item Wallpaper is selected ask users if they want its 3 accessories 
	{
		cout << "Would you like add a Glue?\n"
			<< "1 - Yes\n"
			<< "2 - No\n";
		cin >> accessory_choice;
		switch (accessory_choice)
		{
		case 1:
			item1 = new Glue(item1);//Accessory is added with main item, which gets accessory name and cost, which adds up overallcost of accessory, service/delivery, and main item (everytime object is wrapped with the decorator, cost is incremented).
			//pass the same object as paramater so the properties get wrapped around this object
			break;
		case 2:
			break;
		default://in default no accessory will be added, no item name and cost.
			cout << "Invalid choice.\n";
			break;
		}

		cout << "Would you like add a Scissors?\n"
			<< "1 - Yes\n"
			<< "2 - No\n";
		cin >> accessory_choice;
		switch (accessory_choice)
		{
		case 1:
			item1 = new Scissors(item1);//Accessory is added with main item, which gets accessory name and cost, which adds up overallcost of accessory, service/delivery, and main item (everytime object is wrapped with the decorator, cost is incremented).
			//pass the same object as paramater so the properties get wrapped around this object
			break;
		case 2:
			break;//in default no accessory will be added, no item name and cost.
		default:
			cout << "Invalid choice.\n";
			break;
		}

		cout << "Would you like add a Brush?\n"
			<< "1 - Yes\n"
			<< "2 - No\n";
		cin >> accessory_choice;
		switch (accessory_choice)
		{
		case 1:
			item1 = new Brush(item1);//Accessory is added with main item, which gets accessory name and cost, which adds up overallcost of accessory, service/delivery, and main item (everytime object is wrapped with the decorator, cost is incremented).
			//pass the same object as paramater so the properties get wrapped around this object
			break;
		case 2:
			break;
		default://in default no accessory will be added, no item name and cost.
			cout << "Invalid choice.\n";
			break;
		}

	}

	else {
		cout << "Invalid input" << endl; //user will re-do item browsing
	}
	//setting delivery/service option that user chose
	cout << "-------------------------------------Select Service---------------------------------------" << endl;//Offer users delivery services to choose from for their orders
	cout << "Enter your Choice of service to deliver item:\n"
		<< "0 - Basic Delivery (up to 7 days) (or) 1 - Express Delivery (1-2 days), 2 - Pick-up Delivery\n"; //prints delivery options
	cin >> service_choice;
	item1->setService(service_choice);//setting service to user's service choice
	cout << item1->getService() << endl; //retrieve delivery service chose for order

	cout << item1->getItemName() << " Cost is: $" << item1->cost() << endl;//all decorators that have been wrapped around the object will be retrieved, similar to a stack
	//cost is also retrieved for the item

	cout << "-------------------------------------Personal Details---------------------------------------" << endl;
	if (service_choice == 2) // if service choice is Pick up delivery ask for customers first name, surname, and phone number.
	{
		cout << "Enter First name: " << endl;
		cin >> first_name;
		cin.ignore();

		cout << "Enter Surname: " << endl;
		cin >> customer_surname;
		cin.ignore();

		cout << "Pickup order was chosen" << endl;

		cout << "Enter Phone Number: " << endl;
		cin >> phone_number;
		cin.ignore();
	}

	else if (service_choice == 0 || 1) //if service choice is 0 or 1 then get users first name, surname, phone number and home address for delivery of order
	{

		cout << "Enter First name: " << endl;
		cin >> first_name;
		cin.ignore();


		cout << "Enter Surname: " << endl;
		cin >> customer_surname;
		cin.ignore();

		cout << "Enter Phone Number: " << endl;
		cin >> phone_number;
		cin.ignore();

		cout << "Enter the Address of where you want your order to be delivered to: " << endl;
		getline(cin, delivery_address);
	}
	int order_confirmation;//var of type int to ask user for order confirmation, whether they want to pay for the items and confirm order
	cout << "Confirmation, would you like to pay and confirm this order? (0 = Yes, 1 = No) " << endl;
	cin >> order_confirmation;

	if (order_confirmation == 0)// if user input is 0, create file for the order, and write order and customer details in the file to save order
	{
		invoice.WriteInvoiceToFile(first_name, customer_surname, delivery_address, phone_number, item1->getItemName(), service_choice, outlet.selectOutlet, item1->cost());//passing variables/values of customer and order deatils to write in file (invoice), stores first name, surname, delivery address, phone number, item lists, service choice, outlet selection, overall cost of order
		cout << "Order Completed" << endl;//prints order is completed
	}

	else {
		cout << "No order has been placed" << endl; //prints no order took place
	}

}

void Home::ViewOrders() //reads Invoice, prints file data to console, allowing users to view, cancel or keep order
{
	Invoice invoice;// creating object of Invoice to access its methods
	invoice.ReadInvoiceFromFile();//View/Reads Order Invoice
}

int main()
{
	Home home; //creating object for home to access its method

	bool return_homepage = true;//var of type bool set to true
	while (return_homepage) 
	{
		home.displayOptions(); //loops back to home/options screen after accessing an option
	}

	system("pause");
	return 0;
}