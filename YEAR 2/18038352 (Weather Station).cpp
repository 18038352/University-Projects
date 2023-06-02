#include <iostream>
#include <string>
#include <map>
#include <chrono>  
#include <thread> 
#include <ctime>
#include <conio.h>

using namespace std;


void startup()
{
	cout << "starting system...." << endl;
	cout << "initialising users..." << endl;

	////loads user
	//userObject.initialise();


	//load logger
	cout << "initialising logger" << endl;

	//initialising sensors
	cout << "initialising sensor " << endl;

	cout << "\nsystem startup complete" << endl;

	system("pause");
}

class Model
{

public: 
	
Model() 
{
	retrieveDataFromDatabase();
}
		const string getName() const
		{
			return this->name;
		}
		void setName(const string name)
		{
			this->name = name;
		}
		float getTemp() const
		{
			return temp;
		}
		void setTemp(const float temp) {
			this->temp = temp;
		}
		void retrieveDataFromDatabase()
		{
			setName("Greenhouse");
			setTemp(25);
			
		}



private:

	float temp;
	string name;

};

class Subject 
{
public:

	Subject(string aID, string pass);

	Subject()
	{
		cout << "Enter UserID :" << endl;;
		cin >> id;
		cout << "Enter password :" << endl;
		cin >> password;
		proofID = "";
	}
	string getId()
	{
		return id;
	}
	string getPassword()
	{
		return password;
	}
	void setproofofID(string proof)
	{
		proofID = proof;
	}
	string getproofofID()
	{
		return proofID;
	}

	void loginMenu();

private:
	string id;
	string password;
	string proofID;
};

Subject::Subject(string a, string pass) : id(a), password(pass)

{


	proofID = "";

}



class View 
{
public:

	void printModelDetails(Model *m) const
	{
		cout << "******************************************" << endl;
		cout << "Model Name: " << m->getName() << endl;
		cout << "Temperature: " << m->getTemp() << endl;
		cout << "******************************************" << endl;


		system("pause");
	}

	uint16_t mainMenu()
	{
		//reads input, only if it is not exit, displays choice

		uint16_t input = 0;
		system("cls");
		cout << "Welcome to the Weather Station device simulator" << endl;
		cout << "Choose from the following options" << endl;
		cout << "------------------------------------" << endl;
		cout << "1: Information about program " << endl;
		// if not authorised
		cout << "2: Log in" << endl;

		cout << "3: Temperature Sensor simulator" << endl;

		cout << "4: Kelvin to Fahrenheit Converter" << endl;
		
		cout << "9: Quit" << endl;
		//else if authorised

		cout << "Your choice :";
		cin >> input;

		return input;
	}

	Subject loginMenu()
	{
	
		
		string id;
		string password;
			cout << "Enter username: " << endl;
			cin >> id;
			cout << "Enter password: " << endl;
			cin >> password;
			Subject s(id, password);

			return s;
	

	}


	
};

class AuthenticationInfo
{
private:

	map<string, string> Users; //userID password


public:
	AuthenticationInfo()
	{
		Users.insert(pair<string, string>("BlankUser", "Computer1212"));
		Users.insert(pair<string, string>("AdminUser", "1Admin1"));
	}

	bool validateUser(string name, string password)
	{
		bool validUser = false;
		map<string, string>::iterator itr;
		itr = Users.find(name);
		if (itr != Users.end())
		{
			if (!(itr->second.compare(password)))
			{
				validUser = true;
			}
		}
		return validUser;
	}
};

class ProofofID
{
private:
	string proofID;

public:
	ProofofID() {};
	ProofofID(string aproofID) : proofID(aproofID) {};
	string getproofID()
	{
		return proofID;
	}
	void setproofofID(string aproofID)
	{
		proofID = aproofID;
	}


};



class Authenticator : public AuthenticationInfo
{
public:
	Authenticator() {}

	ProofofID *authenticateUser(Subject &s)
	{
		AuthenticationInfo ainfo;
		ProofofID *proofofID = nullptr;
		string Id = s.getId();
		string pass = s.getPassword();
		string token = "";
		if (ainfo.validateUser(Id, pass))
		{
			cout << "Welcome" << endl;
			cout << "Authenticated" << endl;
			token = encryptDecrypt(Id + pass); //check
			proofofID = new ProofofID(token);
			s.setproofofID(token);
		}

		else {
			cout << "Invalid user ID or passoword, Please try again.";
			return proofofID;
		}
	}

private:
	string encryptDecrypt(string toEncrypt)
	{
		char key = 'A';
		string output = toEncrypt;
		for (int i = 0; i < toEncrypt.size(); i++)
		{
			output[i] = toEncrypt[i] ^ key;
			return output;
		}
	}
};



class Controller 
{
public: 
	Controller(){}

	Controller(Model *model, View *view)
	{
		this->model = model;
		this->view = view;
	}

	void setView(View *view)
	{
		this->view = view;
	}
	
	void setTemp(float temp)
	{
		model->setTemp(temp);
	}
	float getTemp() const
	{
		return model->getTemp();
	}

	void run() 
	{
		
		uint16_t choice = 1;
		Authenticator a;
		Subject s;

		while (choice != 9)
		{
			choice = view->mainMenu();

			switch (choice)
			{
			case 1: //Model details
				view->printModelDetails(model);
				break;

			case 2:
				s = view->loginMenu();
				a.authenticateUser(s);
				break;
	

			case 3:
				TemperatureSensor();
				
			break;

			case 4:
				 KtoF();

				break;

			default:
				break;
			}
		}
	} 



	void TemperatureSensor()
	{
		
		cout << "---------------------------------"  << endl;
		cout << "Temperature is measured in Kelvin" << endl;
		cout << "---------------------------------" << endl;
		
		for (uint16_t i = 1; i < 24; i++)
		{
			
			char opt;
			
			srand(time(NULL));
			int rn = rand() % 373 + 1;
			std::this_thread::sleep_for(std::chrono::seconds(1)), cout << "Time: " << i << " " << "Temperature: " << rn << " " << endl;
		
			if (rn > 313 && rn < 350)
			{
				cout << "Sunny day!, Thermal actuator is fine" << endl;
				cout << "Turn on, Fan = 'F', Radiator = 'R', Turn off devices = 'N' " << endl;
				cin >> opt;
			
				switch (opt)
				{
				case 'F': cout << "Fan has been switched on" << endl;
					break;

				case 'R' :
					cout << "Radiator has been switched on" << endl;
					break;

				case 'N':
					cout << "Both devices are now switched off" << endl;
					break;

				default:
					cout << "Invalid Command" << endl;
					break;

				}
			}

			else if (rn < 313 && rn > 273)
			{
				cout << "It is cold, Thermal actuator is fine" << endl;
				cout << "Turn on, Fan = 'F', Radiator = 'R', Turn off devices = 'N' " << endl;
				cin >> opt;

				switch (opt)
				{
				case 'F': cout << "Fan has been switched on" << endl;
					break;

				case 'R':
					cout << "Radiator has been switched on" << endl;
					break;

				case 'N':
					cout << "Both devices are now switched off" << endl;
					break;

				default:
					cout << "Invalid Command" << endl;
					break;

				}
			}

			else if (rn > 350)
			{
				cout << "Too hot! Thermal actuator needs cool air now" << endl;
				cout << "Turn on, Fan = 'F', Radiator = 'R', Turn off devices = 'N' " << endl;
				cin >> opt;

				switch (opt)
				{
				case 'F': cout << "Fan has been switched on" << endl;
					break;

				case 'R':
					cout << "Radiator has been switched on" << endl;
					break;

				case 'N':
					cout << "Both devices are now switched off" << endl;
					break;

				default:
					cout << "Invalid Command" << endl;
					break;

				}

				

			}

			else if (rn < 273)

			{
				cout << "Temperature is too cold, turn on radiator now!" << endl;
				cout << "Turn on, Fan = 'F', Radiator = 'R', Turn off devices = 'N' " << endl;
				cin >> opt;

				switch (opt)
				{
				case 'F': cout << "Fan has been switched on" << endl;
					break;

				case 'R':
					cout << "Radiator has been switched on" << endl;
					break;

				case 'N':
					cout << "Both devices are now switched off" << endl;
					break;

				default:
					cout << "Invalid Command" << endl;
					break;

				}
			}
		}

	
	}

	void KtoF()
	{
		long double kel, fah;
		cout << "Converting temperature from Kelvin to Fahrenheit : " << endl;
		cout << "----------------------------------------------------" << endl;
		cout << "Enter the Kelvin temperature : ";
		cin >> kel;
		fah = (9.0 / 5) * (kel - 273.15) + 32;
		cout << "The Kelvin temperature : " << kel << endl;
		cout << "The Fahrenheit is : " << fah << endl;

		system("pause");

	}

private:
	Model *model;
	View *view;
};



int main()
{

	
	unsigned userExited = 0;



	while (!userExited)

	{

		Subject s;

		Authenticator a;

		ProofofID *proofofID = a.authenticateUser(s);

		
		if (proofofID != nullptr)

		{
			
			startup();
			uint16_t ui8_userChoice = 0;
			Model *model = new Model;
			View *view = new View;
			Controller c(model, view);
			c.run();

			delete model;
			delete view;

			return 0;


		}

		cout << "EXIT Yes = 1 , No = 0 : ";
		cin >> userExited;
	}

}