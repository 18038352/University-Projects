#include <iostream> // Adds iostream library. Header that defines the standard input and output stream objects.

using namespace std; // Adds standard library.

class Node { //creating a Node class

public: // Makes the class variables below accesible from outside the class.

	int value; //declaring value to data type int
	Node* iNext; // node will point to the next data in the stack
};

class Stack { //declaring a Stack class

private: // Makes data and functions private. 

	int count = 0; //initialising the stack counter to zero (0). Holds the number of elements in the stack (incremented each time push has been called).
	Node* iTop = nullptr; //a pointer that points to the item at the top of the stack
	Node* nodePop(void); // declaring the nodePop function 

public: // Makes the class variables below accesible from outside the class.

	~Stack(void);// deconstructor
	void push(int value);// pushes node on the top of the stack
	int pop(void);//pop top node of the stack
};

Stack::~Stack(void) { //deconstructor to delete all of the dynamic variables
	while (iTop != nullptr) { //check if iTop is not null.
		delete nodePop(); // nodePop is deleted if itop is not null
	}
}

void Stack::push(int value) { //push function define that takes in a parameter type in, which is an element to be added onto the stack
	Node* iTmp = new Node; // creating a new object of type node
	iTmp->value = value; // setting the value of iTmp as the value being past through the parameter.
	iTmp->iNext = iTop;  // setting the current top value of the stack as the next item.


	iTop = iTmp; //point top to the new item of the stack
	count++; //increment by 1 each time new element is added onto the stack
}

Node* Stack::nodePop(void) { // a function that returns the current top value to be popped
	Node* iTmp = iTop; // a pointer object iTmp of type node that has the value of the cureent top item.
	if (iTop != nullptr) iTop = iTop->iNext; //set new iTop to be the next node (the one after the top item that is going to be popped)
	return iTmp;
}

int Stack::pop(void) { // defined to pop or remove top element of the stack
	if (count == 0) throw "Stack Empty!"; // if there is no element in the stack output the message

	Node* iTmp = nodePop(); //declaring a pointer object of type node that calls the nodePop function as its value which returns the current top item of the stack that can be popped. 
	int ret; //variable that holds the int popped value or top value of the stack.

	if (iTmp != nullptr) { // if iTmp is not null
		ret = iTmp->value; //set ret as the current top value to be popped.
	}
	else {
		throw "Error!"; // if iTmp is null output error message.
	}

	delete iTmp; // deletes iTmp
	count--; // decrement, when pop one less element in the stack
	return ret; // return pop value
}






template<typename T> //declaring a template using a parameter type T, enabling to use other standard data types for the stack.
class NodeT // declaring NodeT class
{
public:
	T value; //setting value as generic data types, enabling to use other standard data types for the stack.
	NodeT* iNext = nullptr; // NodeT will point to the next data in the stack

};

template <typename T>
class StackT // declaring StackT class
{
private:
	T count = 0; //initialising the stack counter to zero (0). Holds the number of elements in the stack (incremented each time push has been called).
	NodeT<T> *iTop = nullptr; //a pointer that points to the item at the top of the stack
	NodeT<T>* nodePop(void); // declaring the nodePop function 

public:
	~StackT(void); // deconstructor
	void push(T value); // pushes node on the top of the stack
	T pop(void); //pop top node of the stack

};

template <typename T>
StackT<T>::~StackT(void) //deconstructor to delete all of the dynamic variables
{
	while (iTop != nullptr) //check if iTop is not null.
	{
		delete nodePop(); // nodePop is deleted if itop is not null
	}
}

template <typename T>
void StackT<T>::push(T value) //push function define that takes in a parameter type in, which is an element to be added onto the stack
{
	NodeT<T>* iTmp = new NodeT<T>; // creating a new object of type NodeT
	iTmp->value = value;// setting the value of iTmp as the value being past through the parameter.
	iTmp->iNext = iTop; // setting the current top value of the stack as the next item.
	iTop = iTmp; //point top to the new item of the stack
	count++;  //increment by 1 each time new element is added onto the stack
}

template <typename T>
NodeT<T>* StackT<T>::nodePop(void)  // a function that returns the current top value to be popped
{
	NodeT<T> *iTmp = iTop;  // a pointer object iTmp of type node that has the value of the cureent top item.
	if (iTop != nullptr) iTop = iTop->iNext; //set new iTop to be the next node (the one after the top item that is going to be popped)
	return iTmp;
}

template <typename T>
T StackT<T>::pop(void) // defined to pop or remove top element of the stack
{
	if (count == 0) throw "Stack Empty!"; // if there is no element in the stack output the message

	NodeT<T> *iTmp = nodePop(); //declaring a pointer object of type node that calls the nodePop function as its value which returns the current top item of the stack that can be popped. 
	T ret; //variable that holds the T popped value or top value of the stack.

	if (iTmp != nullptr) // if iTmp is not null
	{
		ret = iTmp->value;  //set ret as the current top value to be popped.
	}
	else
	{
		throw "Error!";  // if iTmp is null output error message.

	}

	delete iTmp; // deletes iTmp
	count--; // decrement, when pop one less element in the stack
	return ret; // return pop value


}