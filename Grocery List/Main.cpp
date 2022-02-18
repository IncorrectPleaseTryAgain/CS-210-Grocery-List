/*
* Name: Michael Steekamp
* Title: Project Three
* File: Main.cpp
* Date: Febuary 11, 2022
* 
* This program prompts user to select one of three options. Depending on which
* option was chosen the corresponding function will or will not be called.
* The general idea of this program is to get a list of items,
* and then calculate their frequency. It then does something to that
* data depending on which option was chosen.
*/
#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <thread>
#include <fstream>
#include <iomanip>

using namespace std;

//options
const unsigned int OPTION_ONE_DISPLAY_LIST = 1;
const unsigned int OPTION_TWO_DISPLAY_SPECIFIC_ITEM = 2;
const unsigned int OPTION_THREE_DISPLAY_HISTOGRAM = 3;
const unsigned int OPTION_FOUR_EXIT_PROGRAM = 4;

//python function names
const string WRITE_OUTPUT_FILE = "writeSortedDataToOutputFile";
const string DISPLAY_ITEMS_AND_FREQUENCY = "displayItemsAndFrequency";
const string DISPLAY_FREQUENCY_FOR_SPECIFIC_ITEM = "returnFrequencyForSpecificItem";

//sorted data file
const string OUTPUT_FILE_NAME = "frequency.dat";


//Python Function
/*
* Pname - python function name
* Return - N/A
* Call python function with no parameter and no return
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
* proc - python function name
* param - string parameter
* Return - N/A
* Call python function with one parameter and no return
*/
void CallProcedure(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(s)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;
}

/*
* proc - python function name
* paramA - string parameter
* paramB - string parameter
* Return - Intiger
* Call python function with two parameters and intiger return
*/
int callIntFunc(string proc, string paramA, string paramB)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[paramA.length() + 1];
	std::strcpy(paramval, paramA.c_str());

	char* paramvalTwo = new char[paramB.length() + 1];
	std::strcpy(paramvalTwo, paramB.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z,z)", paramval, paramvalTwo);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

//Display
void displayOptions()
{
	//clear terminal
	system("CLS");

	cout << "==============================================================" << endl;
	cout << "| Option 1: Display list of items and frequency              |" << endl;
	cout << "|                                                            |" << endl;
	cout << "| Option 2: Display frequency for specific item              |" << endl;
	cout << "|                                                            |" << endl;
	cout << "| Option 3: Display histogram containing items and frequency |" << endl;
	cout << "|                                                            |" << endl;
	cout << "| Option 4: EXIT                                             |" << endl;
	cout << "==============================================================" << endl;
}

void displayExitMessage()
{
	//clear terminal
	system("CLS");

	cout << "============================================" << endl;
	cout << "|                                          |" << endl;
	cout << "|                                          |" << endl;
	cout << "|              END OF PROGRAM!             |" << endl;
	cout << "|                                          |" << endl;
	cout << "|                                          |" << endl;
	cout << "============================================" << endl;
}

/*
* Parameter - N/A
* Return - N/A
* Wait until user presses ENTER to continue program
*/
void pressEnterToContinue()
{
	cout << '\n' << "Press ENTER to continue...";

	//wait for input
	cin.ignore();
	cin.get();
}

//Logic
/*
* value - variable to check
* Return - boolean
* Check if parameter is a double
*/
bool isDouble(double value)
{
	//number rounded up - is equal - number rounded down
	if (floor(value) != ceil(value))
	{
		//value is double
		return true;
	}
	else
	{
		//value is not double
		return false;
	}
}

//Getter
/*
* userOptionDecision - store user input for chosen option
* Return - N/A
* Get user input for which option to execute, check if input is valid
*/
void getUserOptionInput(double& userOptionDecision)
{
	//how long for system sleep/pause
	const unsigned short int SLEEP_INTERVAL = 1;

	//get decision
	cout << "Please Enter Option (1,2, 3 or 4): ";
	cin >> userOptionDecision;

	/*	Do if input is invalid
	*	cin = good or (1 < value < 3) or value = intiger
	*/
	while (cin.fail() || (userOptionDecision < OPTION_ONE_DISPLAY_LIST || userOptionDecision > OPTION_FOUR_EXIT_PROGRAM) || isDouble(userOptionDecision))
	{
		//error message
		cout << "Error: Input Out Of Range" << endl;

		//clear buffer
		cin.clear();
		cin.ignore(256, '\n');

		//wait 1 second
		this_thread::sleep_for(chrono::seconds(SLEEP_INTERVAL));

		displayOptions();

		//get new input
		cout << "Please Enter Option (1,2, 3 or 4): ";
		cin >> userOptionDecision;
	}
}

//Execute
/*
* Parameters - N/A
* Return - N/A
* Display list of items and frequency 
*/
void executeOptionOne()
{
	//clear terminal
	system("CLS");

	//Python function - displayItemsAndFrequency
	CallProcedure(DISPLAY_ITEMS_AND_FREQUENCY, OUTPUT_FILE_NAME);

	pressEnterToContinue();
}

/*
* Parameters - N/A
* Return - N/A
* Display frequency for specific item 
*/
void executeOptionTwo()
{
	//specific item is not in file
	const int NO_ITEM_EXISTS = -1;

	//Item: Name and Frequency
	string specificItemName = "";
	int specificrItemFrequency = NO_ITEM_EXISTS;

	cout << "Please enter specific item: ";
	cin >> specificItemName;

	//format input - Initial: input, Result: Input
	specificItemName[0] = toupper(specificItemName[0]);

	//Python function - returnFrequencyForSpecificItem
	specificrItemFrequency = callIntFunc(DISPLAY_FREQUENCY_FOR_SPECIFIC_ITEM, OUTPUT_FILE_NAME, specificItemName);

	//if item is in file
	if (specificrItemFrequency != NO_ITEM_EXISTS)
	{
		cout << "Results: " << specificItemName << " purchased " << specificrItemFrequency << " times." << endl;
	}
	else if (isdigit(specificItemName[0]))
	{
		cout << "Item cannot be a number." << endl;
	}
	else
	{
		cout << "\'" << specificItemName << "\' was not purchased." << endl;
	}


	pressEnterToContinue();
}

/*
* Parameter - N/A
* Return - N/A
* Display histogram containing items and frequency
*/
void executeOptionThree()
{
	//item - ex. 'Cheese 5'
	string item = "";

	//'Cheese'
	string itemName = "";

	//5
	int itemFrequency = 0;

	//clear terminal
	system("CLS");

	//declare fstream (output)
	fstream file;

	//open file
	file.open(OUTPUT_FILE_NAME);

	//Header
	cout << "     HISTOGRAM" << endl;
	cout << "===================\n" << endl;
	cout << "ITEM NAME" << right << setw(13) << "DATA\n" << endl;

	//if file was opened successfully
	if (file.is_open())
	{
		//read file line by line - store line in 'item'
		while (getline(file, item)) {

			//Split 'item' into name and frequency
			itemName = item.substr(0, item.find(' '));
			itemFrequency = stoi(item.substr(item.find(' '), item.find('\n')));

			//display histogram
			cout << left << setw(15) << itemName << " |";
			for (int i = 0; i < itemFrequency; i++)
			{
				cout << "#";
			}
			cout << endl;
		}

		// Close the file
		file.close();

		pressEnterToContinue();
	}
	else //file was not opened successfully
	{
		cout << "Fail: Could Not Open File";
		pressEnterToContinue();
	}
}

int main()
{
	//user decision
	double userOptionNumber = 0.0;

	//python function - writeSortedDataToOutputFile
	CallProcedure(WRITE_OUTPUT_FILE, OUTPUT_FILE_NAME);

	//while user doen't want to exit program
	while (userOptionNumber != OPTION_FOUR_EXIT_PROGRAM)
	{
		displayOptions();

		//get user decision
		getUserOptionInput(userOptionNumber);

		//execution according to user decision
		if (userOptionNumber == OPTION_ONE_DISPLAY_LIST)
		{
			//Display list of items and frequency 
			executeOptionOne();
		}
		else if (userOptionNumber == OPTION_TWO_DISPLAY_SPECIFIC_ITEM)
		{
			//Display frequency for specific item
			executeOptionTwo();
		}
		else if (userOptionNumber == OPTION_THREE_DISPLAY_HISTOGRAM)
		{
			//Display histogram
			executeOptionThree();
		}
	}

	displayExitMessage();

	return 0;
}