#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <conio.h>

using namespace std;

// declares a bool to used for continuing while loop in main
bool CONTINUE_RUN = true;

//displays menu options, validates user selection is 1, 2, or 3,
int displayMenu() {
	int userInput = 0;
	while (true) {

		cout << "1: Display a Multiplication Table" << endl;
		cout << "2: Double a Value" << endl;
		cout << "3: Exit" << endl;
		cout << "Enter your selection as a number 1, 2, or 3." << endl;

		//ensure that user input is an integer and if not continues asking for input until user inputs an integer
		while (!(cin >> userInput)) {
			system("cls");
			cout << "ERROR: Please enter 1, 2, or 3" << endl;
			cout << "1: Display a Multiplication Table" << endl;
			cout << "2: Double a Value" << endl;
			cout << "3: Exit" << endl;
			cout << "Enter your selection as a number 1, 2, or 3." << endl;

			cin.clear();
			cin.ignore(123, '\n');
		}
		//breaks loop and returns 1
		if (userInput == 1) {
			break;
		}
		//breaks loop and returns 2
		if (userInput == 2) {
			break;
		}
		//breaks loop and sets bool to false to end while loop in main
		if (userInput == 3) {
			CONTINUE_RUN = false;
			break;
		}
		//requests user input integer
		else {
			system("cls");
			cout << "ERROR: Please enter 1, 2, or 3" << endl;
			continue;
		}
	}
	return userInput;
}
// prompts user to enter integer for calculations
int userData() {
	int pickNum;
	system("cls");
	cout << "Please enter an integer: " << endl;

	//ensures user entry is an integer
	while (!(cin >> pickNum)) {
		system("cls");
		cout << "ERROR:" << endl; 
		cout << "Please enter an INTEGER: " <<endl;
		cin.clear();
		cin.ignore(123, '\n');
	}
	//returns user entered integer
	return pickNum;
}

//calls functions from python file returns integer **Provided as Starter Code**
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonFile3");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
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

	return _PyLong_AsInt(presult);
}

//call functions to display menu and recieve user input. based on returned user input calls right function in .py file
int main() {
	
	//while loop continues until user input alters CONTINUE_RUN bool
	while (CONTINUE_RUN == true) {
		int userNumber = 0;
		int menuValue = displayMenu();
		if (menuValue == 1) {
			userNumber = userData();
			system("cls");
			cout << "Multiplication Table for " << userNumber << " is:" << endl;
			// used int token to accept and ignore returned int from .py function, printing happens in .py
			int token = callIntFunc("MultiplicationTable", userNumber);
			cout << endl;
			cout << "Press any key to continue..." << endl;
			_getch();
			system("cls");

		}
		if (menuValue == 2) {
			userNumber = userData();
			system("cls");
			cout << "The number " << userNumber << " doubled is ";
			//uses c++ to format output and prints value returned from .py function
			cout << callIntFunc("DoubleValue", userNumber) << endl;
			cout << endl;
			cout << "Press any key to continue..." << endl;
			_getch();
			system("cls");

		}
	}
	//prints exit message when while loop is exited
	system("cls");
	cout << "*************" << endl;
	cout << "Rip and Tear!" << endl;
	//       Until it is DONE!
	cout << "GOODBYE" << endl;
	cout << "*************" << endl;
}
