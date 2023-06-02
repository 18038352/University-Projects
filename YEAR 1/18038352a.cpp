#pragma once //stops duplicate library includes.
#include<iostream> // Adds iostream library. Header that defines the standard input and output stream objects.
#include<fstream> // Adds fstream library.
#include<string> // Adds string library.
#include<vector> // Adds vector library.

using namespace std; // Adds standard library.

class SalesData // Creating class.
{

private:
	ifstream inputfile; // Used to read from already created files.
	ofstream outputfile; // Used to create files, as well as writing in them.
	vector <int> salesrecords; // This stores the sales records data. A vector of type int that holds sales records.

public:

	// Creating functions.
	void loadDataFromFile(string sales);
	void saveBarChartToFile(string saleschart);

};


void SalesData::loadDataFromFile(string sales) // This function displays the text file in the console.



{
	int SalesData = 0; // Creates a variable with a data type of int called SalesData and is equal to zero.

	salesrecords.clear(); // Clean out any old data.
	inputfile.open(sales);//open input file.

	if (!inputfile) // To check if file exist 
	{
		cout << "Error!" << sales << "File does not exist" << endl;
		return;
	}

	while (inputfile >> SalesData) // Data from the loop will be stored with the SalesData.

	{
		cout << SalesData << endl; // Displays SalesData.
		salesrecords.push_back(SalesData); //save the data in vector.
	}

	inputfile.close(); // File will close.

}

void SalesData::saveBarChartToFile(string saleschart) // Function that collect Sales Data and display it on saleschart.

{
	if (salesrecords.size() == 0) // If there is no sales record, message below will display.
	{
		cout << "Error! No sales data available" << endl;
		return;
	}

	outputfile.open(saleschart); // opens saleschart text file.

	if (!outputfile) //check if file exist
	{
		cout << "Error!" << saleschart << "File cannot open" << endl;
		return;
	}
	
	else {

		outputfile << "SALES BAR CHART" << '\n' << "(EACH * IS EQUAL TO £100)" << endl; //display titles of the text file.

	}

	int counter = 1; //store counter, starts from 1.
	for (int count = 0; count < salesrecords.size(); count++) // For-loop that iterates through the salesrecords vector.           

	{
	    int noofstars = salesrecords[count] / 100; //calculates the correct number of stars to the nearest 100.
		outputfile << "Store " << counter << ": "; //display "Store" in text file, and counter to represent number of store.
		for (int starcount = 0; starcount < noofstars; starcount++) // the for loop that prints out "*" based on the number of stars calculated from star count.
		{
			outputfile << "*"; //stars saved in file.
		}
		counter++; //increment by 1
		outputfile << endl; // go to next line of file.
		
	}


	outputfile.close(); // closes saleschart text file.
}



int main(void) //First function that runs.
{

	
	SalesData salesdataobject; // Using the class SalesData, we will create an object called "salesdataobject".
	salesdataobject.loadDataFromFile("sales.txt"); // Using salesdataobject to load the loadDataFromFile.
	salesdataobject.saveBarChartToFile("saleschart.txt"); // Using salesdataobject to load the saveBarChartToFile.


	return 0; // Ends main function.
}
