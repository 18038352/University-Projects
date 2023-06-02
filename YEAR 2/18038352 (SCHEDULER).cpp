#include <iostream>// Adds iostream library. Header that defines the standard input and output stream objects.
using namespace std;// Adds standard library.



class Node //declaring a Node class
{
public: // Allows the class variables below accesible from outside the class.
	Node(int value, Node* nextptr = NULL, Node* prevptr = NULL, int currentpriority = 0)
	{
		this->value = value;
		next = nextptr;
		prev = prevptr;
	}
	//Constructor with variables in parameters

	Node() = default; //creates default constructor

	int getVal(void)
	{
		return value;    //gets the private member value to return its value
	}

	void setVal(int val)
	{
		value = val; // sets the private member value to set the value.
	}
	Node* getNext(void)
	{
		return next;
	}
	Node* getPrev(void)
	{
		return prev;
	}

	void setPrev(Node* prevptr)
	{
		prev = prevptr;
	}
	void setNext(Node* nextptr)
	{
		next = nextptr;
	}
	int getPriority(void)
	{
		return priority;
	}

	void setPriority(int p)
	{
		priority = p;
	}

	//getters and setters method to access private members, encapsulation.




private: //the class variables below will be inaccessible.
	Node* next;
	Node* prev;
	int priority;
	int value;
	//declares private members
};

//declares a Stack class
class Stack : public Node //using inheritance, to gain access of Node class public and private members.
{
public: // Allows the class variables below accesible from outside the class, stack public members and functions.


	Stack() { //Contructor
		top = nullptr; // sets top equal to null
	}

	~Stack() { //deconstructor
		while (top != nullptr)  //checks if top is not null
			delete NodePop(); // NodePop will be deleted when top is not null 
	}

	//int i is int value
	void Push(int i) //Push function that takes in a parameter of type int, element is added to the stack, node is pushed on the top of the stack.
	{
		Node* tmp = new Node(i, top); //creates new object of type node which takes in a parameter of type int and variable top
		top = tmp; // points top to the new item of stack
	}

	int Pop() //pop function removes top element of the stack
	{
		int ret = 0; // default value
		if (top != nullptr)
		{
			ret = top->getVal(); //sets ret to be the top value to be popped
			Node* tmp = top; //declares pointer object of type node that calls top as its value, then returns the current top element of the stack to pop.
			top = top->getNext(); // sets top as next value in stack
			delete tmp;//tmp is deleted

		}
		else
			throw "Stack Empty"; //exception, outputs the message in console when zero item is in stack

		return ret; //returns pop value



	}



	Node* NodePop(void) // function which return the current top value to be popped
	{
		Node* tmp = top; //pointer object tmp of type node that has value of current top item
		if (top != nullptr) //if top is not equal to null then
		{
			top = top->getNext(); //set the new top to be the next node, which is the one after the top item that will be popped
		}
		return tmp; // return current top item
	}

private:  // class variables below inaccessible.
	Node* top; //pointer variable, points to the item at the top of stack

};



class Queue : public Node // declares queue class, use inheritance to get access of the class node attributes
{

private:  //class variables below inaccessible.
	virtual Node* NodeDequeue(void);

protected: // Variables can only be accessed in subclasses or in thisclass
	Node* back;
	Node* front;
	//Nodes which will point to both the back and front of queue


public: // enables the class variables below to be accesible from outside the class.



	Queue(void) //Queue constructor
	{
		front = back = NULL; // setting front and back to null to construct an empty queue
	}

	~Queue(void) // deconstructor
	{
		while (front != NULL) { delete NodeDequeue(); } // while loop when front is not null then delete NodeDequeue
	}

	void Enqueue(int i, int priority = 0) // function to queue items that holds int variables as parameter
	{
		Node* tmp = new Node(i, back); //Creates pointer object of type node putting item at the back of the queue
		back = tmp; //sets back as tmp value
		if (front == nullptr) { // if front = null, then run this function.
			front = back; //setting front as the value of back
			this->setNext(front);//setting setNext parameter as front the value this pointer is used to retrieve the object
			this->setVal(i); //setting setVal parameter to i
		}
		else { //if not equal to null then run this function
			this->setVal(i); //setting setVal parameter to i
			this->setNext(back); //setting setNext parameter as back
			tmp = back->getNext(); //setting tmp to getNext returned value
			tmp->setPrev(back);//setting parameter as back value
		}
	}


	int Dequeue(void) //function to dequeue items
	{
		Node* tmp = NodeDequeue(); //declares a pointer object of type node that calls the function as its value
		int ret = tmp->getVal(); //sets ret as top value to be dequeued
		if (tmp != nullptr) //if tmp is not null then run this
		{
			ret = tmp->getVal(); //setting ret as top value to be dequeued
		}

		else // if tmp is null
		{
			throw "Queue Empty"; //exception and output this msg
		}
		if (front == nullptr) back = front; //if front is = null, set back to equal to front
		return ret; // return ret value
	}
};

Node* Queue::NodeDequeue(void)
{
	Node* tmp = front; //sets tmp to front val
	if (front != nullptr) //run this, iffront is not equal to null
	{
		front = front->getPrev(); //front is = (equal) to returned value of getPrev
		if (front != nullptr) front->setNext(nullptr); //if front is not equal to null, then front is equal to the returned value of setNext, with parmeter that holds null
	}

	return tmp; // return current top item
};



class Scheduler : public Queue // declares scheduler class, which is a subclass of queue
{
private:
	Node* NodeDequeue(void); // private member which is a virtual variable from the queue class
};


