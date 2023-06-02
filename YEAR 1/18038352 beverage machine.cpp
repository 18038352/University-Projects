
#include <iostream>
#include <vector>

using namespace std;

//Enumeration of the different states
enum state { Out_Of_Chocolate, No_Credit, Has_Credit, Dispenses_Chocolate, Maintenance_Mode };

//declaring StateContext class
class StateContext;

//declaring State class
class State
{
protected:
	// Pointer of type StateContext that points to the current context.
	StateContext* CurrentContext;
public:
	// A constructor within a parameter that initialises the pointer.
	State(StateContext* Context) { CurrentContext = Context; }
	// Virtual destructor
	virtual ~State(void) {}
};

//Declaring StateContext class
class StateContext
{
protected:
	// Pointer of type State which points to null.
	State* CurrentState = nullptr;
	// Field of type index that holds the index of the state.
	int stateIndex = 0;
	// A vector that holds objects of type State - the available states.
	vector <State*> availableStates;
public:
	// Virtual destructor
	virtual ~StateContext(void);
	// Virtual method, which is a mutator that sets the new state.
	virtual void setState(state newState);
	// Virtual method, an accessor that gets the current state index.
	virtual int getStateIndex(void);
};

// Defined the StateContext destructor
StateContext::~StateContext(void)
{
	// Deletes available states
	for (int i = 0; i < this->availableStates.size(); i++) delete this->availableStates[i];
	// Deletes all elements in the availableStates vector, as vector size is set to 0.
	this->availableStates.clear();
}

//Defines the set state method 
void StateContext::setState(state newState)
{
	//updating the state of the vending machine, updating the system, e.g. changes thats been applied.
	this->CurrentState = availableStates[newState];
	this->stateIndex = newState;
}

//StateContext of type int that gets State Index
int StateContext::getStateIndex(void) 
{
	return this->stateIndex;
}

//defined the transition class
class Transition
{
public:

	//virtual methods of type bool that prints "error" if statement is false, e.g. not enough money for chocolates.
	virtual bool insertMoney(int) { cout << "Error!" << endl; return false; }
	virtual bool makeSelection(int) { cout << "Error!" << endl; return false; }
	virtual bool moneyRejected(void) { cout << "Error!" << endl; return false; }
	virtual bool addChocolate(int) { cout << "Error!" << endl; return false; }
	virtual bool dispense(void) { cout << "Error!" << endl; return false; }
	virtual bool enterPin(int pin) { cout << "Error!" << endl; return false; }
	virtual bool exit(void) { cout << "Error!" << endl; return false; }
};

//defining ChocoState class, public state and public transition
class ChocoState : public State, public Transition
{
public:
	//Enabling state and transition to operate within chocostate, e.g. all transitions will cause change in chocostate.
	ChocoState(StateContext* Context) : State(Context) {}
};

//OutOfChocolate class
class OutOfChocolate : public ChocoState
{
public:
	//declaring functions of type bool to procceed through payment process of the vending machine
		//declaring functions of type bool
	OutOfChocolate(StateContext* Context) : ChocoState(Context) {}
	bool addChocolate(int number);
	bool enterPin(int pin);
	bool moneyRejected(void);
};

//defining NoCredit class 
class NoCredit : public ChocoState
{
public:
	//if there is not enough credit, transaction reset will occur.
		//declaring functions of type bool
	NoCredit(StateContext* Context) : ChocoState(Context) {}
	bool insertMoney(int credit);
	bool enterPin(int pin);
};

//defining HasCredit Class
class HasCredit : public ChocoState
{
public:
	//checks if theres enough money/credit to complete transaction and dispense the chocolates
	//declaring functions of type bool
	HasCredit(StateContext* Context) : ChocoState(Context) {}
	bool insertMoney(int credit);
	bool makeSelection(int option);
	bool moneyRejected(void);
};

//defining Dispenseschocolate class 
class DispensesChocolate : public ChocoState
{
public:

	//declaring function of type bool to dispense chocolate
	DispensesChocolate(StateContext* Context) : ChocoState(Context) {}
	bool dispense(void);
};

//defining maintenance mode class
class MaintenanceMode : public ChocoState
{
public:
	//declaring functions of type bool, declaration of this class will enable vending machine to activate maintenance mode
	MaintenanceMode(StateContext* Context) : ChocoState(Context) {}
	bool exit(void);
	bool addChocolate(int number);
};

//defining chocolate_dispenser class
class Chocolate_Dispenser : public StateContext, public Transition
{
	//friend classes which access the protected members of the classes, or in this case access enum state
	friend class OutOfChocolate;
	friend class NoCredit;
	friend class HasCredit;
	friend class DispensesChocolate;
	friend class MaintenanceMode;
private:
	int inventory = 0; //number of chocolate
	int credit = 0; //a measure of the number of bars that can be purchased and not money
	int pin = 54321; //secret pin for maintenance mode - *DO NOT CHANGE*
public:
	//setting all stages of type bool as public members, so can be accessible for the main function
	Chocolate_Dispenser(void);
	bool insertMoney(int credit);
	bool makeSelection(int option);
	bool moneyRejected(void);
	bool addChocolate(int number);
	bool dispense(void);
	bool enterPin(int pin);
	bool exit(void);
};


Chocolate_Dispenser::Chocolate_Dispenser(void)
{
	//adds changes to availablestates vector
	this->availableStates.push_back(new OutOfChocolate(this));
	this->availableStates.push_back(new NoCredit(this));
	this->availableStates.push_back(new HasCredit(this));
	this->availableStates.push_back(new DispensesChocolate(this));
	this->availableStates.push_back(new MaintenanceMode(this));
	//updates all changes to vector
	this->setState(Out_Of_Chocolate);
}

//declaring what each stages should do

bool Chocolate_Dispenser::insertMoney(int credit)
{
	return ((ChocoState*)CurrentState)->insertMoney(credit);
}
bool Chocolate_Dispenser::makeSelection(int option)
{
	return ((ChocoState*)CurrentState)->makeSelection(option);
}
bool Chocolate_Dispenser::moneyRejected(void)
{
	return ((ChocoState*)CurrentState)->moneyRejected();
}
bool Chocolate_Dispenser::addChocolate(int number)
{
	return ((ChocoState*)CurrentState)->addChocolate(number);
}
bool Chocolate_Dispenser::dispense(void)
{
	return ((ChocoState*)CurrentState)->dispense();
}

bool Chocolate_Dispenser::enterPin(int pin)
{
	return ((ChocoState*)CurrentState)->enterPin(pin);
}

bool Chocolate_Dispenser::exit(void)
{
	return ((ChocoState*)CurrentState)->exit();
}

//function to add chocolates
bool OutOfChocolate::addChocolate(int number)
{
	((Chocolate_Dispenser*)CurrentContext)->inventory += number;
	cout << "Adding chocolate... Inventory = " << ((Chocolate_Dispenser*)CurrentContext)->inventory << endl;
	CurrentContext->setState(No_Credit);
	return true;
}

//function that enables to activate maintenance mode if chocolate is out of stock
bool OutOfChocolate::enterPin(int pin)
{
	if (pin == ((Chocolate_Dispenser*)CurrentContext)->pin) {
		cout << "Pin is valid! Entering maintenance mode..." << endl;
		CurrentContext->setState(Maintenance_Mode);
		return true;
	}
	else {
		cout << "Pin is invalid!" << endl;
		return true;
	}
}

// function that rejects money if not enough credit 
bool OutOfChocolate::moneyRejected(void)
{
	cout << "Rejecting money...." << endl;
	((Chocolate_Dispenser*)CurrentContext)->credit = 0;
	CurrentContext->setState(Out_Of_Chocolate);
	return true;
}

//function to present credit availability
bool NoCredit::insertMoney(int credit)
{
	((Chocolate_Dispenser*)CurrentContext)->credit += credit;
	cout << "Adding credit... Credit = " << ((Chocolate_Dispenser*)CurrentContext)->credit << endl;
	CurrentContext->setState(Has_Credit);
	return true;
}

//function to access maintenance mode if no credit is left for cash change.
bool NoCredit::enterPin(int pin)
{
	if (pin == ((Chocolate_Dispenser*)CurrentContext)->pin) {
		cout << "Pin is valid! Entering maintenance mode..." << endl;
		CurrentContext->setState(Maintenance_Mode);
		return true;
	}
	else {
		cout << "Pin is invalid!" << endl;
		return true;
	}
}

//function to take in credit
bool HasCredit::insertMoney(int credit)
{
	((Chocolate_Dispenser*)CurrentContext)->credit += credit;
	cout << "Adding credit... Credit = " << ((Chocolate_Dispenser*)CurrentContext)->credit << endl;
	CurrentContext->setState(Has_Credit);
	return true;
}

//function to make selection after credit is put in
bool HasCredit::makeSelection(int option)
{
	cout << "You have selected " << option << " bar(s) of chocolate" << endl;

	if (((Chocolate_Dispenser*)CurrentContext)->inventory < option) {
		cout << "Error: you have selected more chocolate than the machine contains" << endl;
		return true;
	}

	if (((Chocolate_Dispenser*)CurrentContext)->credit < option) {
		cout << "Error: you don't have enough money for that selection" << endl;
		CurrentContext->setState(Has_Credit);
		return true;
	}

	cout << "Credit and inventory is sufficient for you selection" << endl;

	((Chocolate_Dispenser*)CurrentContext)->inventory -= option;
	((Chocolate_Dispenser*)CurrentContext)->credit -= option;

	CurrentContext->setState(Dispenses_Chocolate);

	return true;
}

//function that rejects transaction if not enough credit for order
bool HasCredit::moneyRejected(void)
{
	cout << "Rejecting money....." << endl;
	((Chocolate_Dispenser*)CurrentContext)->credit = 0;
	CurrentContext->setState(No_Credit);
	return true;
}

//function that shows order and updates vending machine status
bool DispensesChocolate::dispense(void)
{
	cout << "Dispensing..." << endl;
	cout << "Inventory = " << ((Chocolate_Dispenser*)CurrentContext)->inventory << endl;
	cout << "Credit = " << ((Chocolate_Dispenser*)CurrentContext)->credit << endl;

	if (((Chocolate_Dispenser*)CurrentContext)->inventory == 0) CurrentContext->setState(Out_Of_Chocolate);
	else if (((Chocolate_Dispenser*)CurrentContext)->credit == 0) CurrentContext->setState(No_Credit);
	else CurrentContext->setState(Has_Credit);
	return true;
}

//function to that provides information about vending machines current status
bool MaintenanceMode::exit(void)
{
	if (((Chocolate_Dispenser*)CurrentContext)->inventory > 0 && ((Chocolate_Dispenser*)CurrentContext)->credit == 0) {
		cout << "No more credit..." << endl;
		CurrentContext->setState(No_Credit);
		return true;
	}
	else if (((Chocolate_Dispenser*)CurrentContext)->inventory > 0 && ((Chocolate_Dispenser*)CurrentContext)->credit >> 0) {
		cout << "You still have credit left..." << endl;
		CurrentContext->setState(Has_Credit);
		return true;
	}
	else {
		cout << "Inventory is empty or there is some other error!" << endl;
		CurrentContext->setState(Out_Of_Chocolate);
		return true;
	}
}

//allowing to procceed the adding of chocolate in maintenance mode
bool MaintenanceMode::addChocolate(int number)
{
	return true;
}

int main(void) {

	//creating object
	Chocolate_Dispenser chocolateDispenser;

	//using object to run the functions/stages of vending machine

	/*chocolateDispenser.enterPin(54321);*/
	chocolateDispenser.addChocolate(20);
	chocolateDispenser.makeSelection(2);
	chocolateDispenser.insertMoney(10);
	chocolateDispenser.makeSelection(20);
	chocolateDispenser.makeSelection(10);
	chocolateDispenser.insertMoney(10);
	chocolateDispenser.dispense();
	/*chocolateDispenser.exit();*/

	return 0;
}