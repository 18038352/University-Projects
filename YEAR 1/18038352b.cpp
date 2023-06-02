#pragma once //stops duplicate library includes.
#include<iostream> // Adds iostream library. Header that defines the standard input and output stream objects.
#include<fstream> // Adds fstream library.
#include<string> // Adds string library.
#include<vector> // Adds vector library.

using namespace std; // Adds standard library.

class OrganisationRecord // Creating class. 
{
private: // Makes data and functions private. Not used as it can only access private data and functions inside this class.

public: // Makes the class variables below accesible from outside the class.

	string name; // A class variable of type string that holds name.
	string occupation; // A class variable of type string that holds occupation.
	string department; // A class variable of type string that holds department.

};

class HRRecord // Creating class. 
{
private: // Makes data and functions private. Not used as it can only access private data and functions inside this class.

public: // Makes the class variables below accesible from outside the class.


	string address; // A class variable of type string that holds address.
	string phonenumber; // A class variable of type string that holds phonenumber.
	string ninumber; // A class variable of type string that holds ninumber.

};

class PayrollRecord // Creating class. 

{
private: // Makes data and functions private. Not used as it can only access private data and functions inside this class.

public: // Makes the class variables below accesible from outside the class.

	string ninumber; // A class variable of type string that holds ninumber.
	double salary; // A class variable of type double that hold salary.
};

class PayrollProcessing // Creating class. 

{
private:

	ifstream inputfile; // Used to read from already created files.
	ofstream outputfile; // Used to create files, as well as writing in them.
	vector<OrganisationRecord> OrganisationRecords; // A vector of type OrganisationRecord that holds the data of employees within OrganisationRecords.
	vector<HRRecord> HRRecords; // A vector of type HRRecord that holds HR records of employees.
	vector<PayrollRecord> PayrollRecords; // A vector of type PayrollRecord that holds payroll records of employees.

public:

	// Creating functions.
	void loadOrganisationRecords(string filename);
	void loadHRRecords(string filename);
	void loadPayrollRecords(string filename);
	void displayEmployeeOfSalaryGTE(double salary); // gte = greater than or equal to



};

void PayrollProcessing::loadOrganisationRecords(string filename) // This is loading the Organisation Records, ready to display using a different function.

{
	inputfile.open(filename); // Opens the text file.

	if (!inputfile) // Identify if file exists, if there is no file, it will display the error message below.

	{
		cout << "Error! File:" << filename << "does not exist!" << endl;

		return;

	}

	OrganisationRecord newRec; //Creating an object of OrganisationRecord.
	int employeeNumber; // Counts the set of data when loops through the text file.

	while (inputfile >> employeeNumber) // Data from the loop will be stored with the employee number.
	{
		inputfile.ignore(); // Ignores first line of text; e.g. "0001" (employeeNumber) as it is not needed.
		getline(inputfile, newRec.name); // Getting the line of the text and setting the returned texts as the data of name.
		getline(inputfile, newRec.occupation); // Getting the line of the text and setting the returned text as the data of occupation.
		getline(inputfile, newRec.department); // Getting the line of the text and setting the returned text as the data of department.
		OrganisationRecords.push_back(newRec); // Adds newRec to OrganisationRecords vector.
	}
	inputfile.close(); // File will close.
}


void PayrollProcessing::loadHRRecords(string filename) // This is loading the HR Records, ready to display using a different function.

{
	inputfile.open(filename); // Opens the text file.

	if (!inputfile) // Identify if file exists, if there is no file, it will display the error message below.

	{
		cout << "Error! File:" << filename << "does not exist!" << endl;

		return;

	}

	HRRecord newRec;  //Creating an object of HRRecord.
	int employeeNumber; // Counts the set of data when loops through the text file.

	while (inputfile >> employeeNumber) // Data from the loop will be stored with the employee number.

	{
		inputfile.ignore(); // Ignores first line of text; e.g. "0001" (employeeNumber) as it is not needed.
		getline(inputfile, newRec.address); // Getting the line of the text and setting the returned texts as the data of address.
		getline(inputfile, newRec.phonenumber); // Getting the line of the text and setting the returned values as the data of phonenumber.
		getline(inputfile, newRec.ninumber);  // Getting the line of the text and setting the returned values as the data of ninumber.
		HRRecords.push_back(newRec); // Adds newRec to HRRecords vector.
	}
	inputfile.close(); // File will close.
}

void PayrollProcessing::loadPayrollRecords(string filename) // This is loading the Payrolll Records, ready to display using a different function.

{
	string salary; // Declaring a variable called salary with data type of string.

	inputfile.open(filename); // Opens the text file.

	if (!inputfile) // Identify if file exists

	{
		cout << "Error! File:" << filename << "does not exist!" << endl;

		return;

	}

	PayrollRecord newRec; //Creating an object of PayrollRecord.
	int employeeNumber; // Counts the set of data when loops through the text file.

	while (inputfile >> employeeNumber) // Data from the loop will be stored with the employee number.
	{
		PayrollRecord tmp; // Declaring a variable to hold data of a PayRecord class.
		inputfile.ignore(); // Ignores first line of text; e.g. "0001" (employeeNumber) as it is not needed.
		getline(inputfile, tmp.ninumber); // Getting the line of the text and setting the returned values as the data of tmp.
		getline(inputfile, salary); // Getting the line of the text and setting the returned values as the data of salary.
		tmp.salary = stod(salary); // Casting salary to double and setting it as the value for tmp's salary
		PayrollRecords.push_back(tmp); // Adds tmp to the vector of PayrollRecords.
	}
	inputfile.close(); // File will close.
}




void PayrollProcessing::displayEmployeeOfSalaryGTE(double salary) // This display the list of employees that earn greater or equal to the salary specified within the parameter of the function.
{

	// Resize PayrollRecords and HRRecords vector to the size of the OrganisationRecords to avoid out of bounds error.
	PayrollRecords.resize(OrganisationRecords.size());
	HRRecords.resize(OrganisationRecords.size());

	for (int check = 0; check < OrganisationRecords.size(); check++) // For-loop that iterates through the PayrollRecords vector to check salaries that are greater than the specified salary.                    

	{
		if (PayrollRecords[check].salary >= salary) // Conditional statement that check salaries that are greater than or equal to the specified salary within PayrollRecords vector.
		{
			// Display the employees with GTE salary specified.
			cout << OrganisationRecords[check].name << '\n' << HRRecords[check].address << '\n' << OrganisationRecords[check].department << '\n' << PayrollRecords[check].salary << endl;
		}
	}



}

int main(void) //First function that runs.
{
	PayrollProcessing payrollProcessingObject; // Using the class PayrollProcessing, we will create an object called "payrollProcessingObject".
	payrollProcessingObject.loadOrganisationRecords("organisationRec.txt"); // Using payrollProcessingObject to load the loadOrganisationRecords.
	payrollProcessingObject.loadHRRecords("hrRec.txt"); // Using payrollProcessingObject to load the loadHRRecords.
	payrollProcessingObject.loadPayrollRecords("payrollRec.txt"); // Using payrollProcessingObject to load the loadPayrollRecords.
	payrollProcessingObject.displayEmployeeOfSalaryGTE(20000); // Using payrollProcessingObject to load the displayEmployeeOfSalaryGTE.

	return 0; // Ends main function.

}