/**************************************************
 Project: Assignment 1
 Author: Cheryl Neoh Yi Ming
 Purpose: The Tally Ho Probability Generator
**************************************************/
# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <ctime>
using namespace std;

// declaring global variables
const int MAX_SUM_OF_TWO_DICE = 13;
vector<string> tallyData;				// Task 3
int diceToRoll;							// Task 4
int rollsRequired;						// Task 4
int tallyResults[MAX_SUM_OF_TWO_DICE];	// Task 4

// declaring functions
void runMenu();							// Task 1
void displayMenu();						// Task 1 additional function
void displayText(string fileName);	    // Task 2
void createLists(string fileName);		// Task 3 
string generateTable();					// Task 4 generating the table
string displayTable();					// Task 4 displaying the table additional function to split functionality
void saveData(string fileName, string currentTable); // Task 5
void loadData(string fileName);			// Task 6

int main() {
	runMenu();
	system("pause");
}

void runMenu() { // Task 1: Create and Display a Menu
	// delcaring local variables
	string userInput = " ";
	string currentTable;

	while (true) {
		// displaying the menu
		displayMenu();

		// asking user for input
		cout << " Which option would you like (0-5): ";
		cin >> userInput;

		// branching user's input
		if (userInput == "0"){
			cout << "\n Thank you for testing this application.\n\n\t";
			break;
		}

		else if (userInput == "1") { // Task 2: Display an information Screen
			displayText("TallyAbout.txt");
		}

		else if (userInput == "2") { // Task 3: Read and Store Data from a File
			createLists("savedTallyData.txt");
		}

		else if (userInput == "3") { // Task 4: Generate and Display a Dice Tally Table
			cout << "\n How many dice to roll (1-2): ";
			cin >> diceToRoll;

			// validate rollsRequired and diceToRoll
			if (diceToRoll > 2) {
				cout << "\n Invalid number of dices, only 1 or 2 dice.\n\t";
				system("pause");
				system("cls");
				continue;
			}
			cout << " How many rolls required (1-10): ";
			cin >> rollsRequired;			
			if (rollsRequired > 10) {
				cout << "\n Invalid number of rolls, only between 1-10 rolls.\n\t";
				system("pause");
				system("cls");
				continue;
			}

			// generate random seed
			srand(unsigned(time(NULL)));

			// displaying the generated table
			currentTable = "\t" + generateTable() + "\n";
			cout << "\n" + currentTable + "\t";
		}

		else if (userInput == "4") { // Task 5: Save a Dice Table to a File
			// display the last generated Dice Table and ask the user if they want to save the data
			cout << "\n" + currentTable << "\n Do you want to save this data? (y/n) ";
			cin >> userInput;

			// save the data according to user input
			if (userInput == "y") {
				saveData("savedTallyData.txt", currentTable);
			}
			else if (userInput == "n") {
				cout << "\tSaving data terminated.\n";
			}
			else {
				cout << "\n Invalid input..only (y/n) !\n\t";
			}
		}

		else if (userInput == "5") { // Task 6: Load Saved Dice Tables from a File
			loadData("savedTallyData.txt");
		}

		else {
			cout << " Invalid option! only numbers from 0-5.\n\n\t";
		}

		// wait before exit
		system("pause");
		system("cls");
	}
}

void displayMenu() {
	// displaying the Menu title
	cout << string(43, '~') << endl;
	cout << "    The Tally Ho Probability Generator" << endl;
	cout << string(43, '~') << endl;

	// displaying the Menu options
	cout << " [0] End Testing the Program\n";
	cout << " [1] Display \"About\" Information\n";
	cout << " [2] Read and store data from files\n";
	cout << " [3] Generate a Dice Tally Table\n";
	cout << " [4] Save Tally Statistics to a file\n";
	cout << " [5] Load Tally Statistics from a file\n";
	cout << string(44, '~') << endl;
}

void displayText(string fileName) { // Task 2: Display an information Screen
	// declaring local variables
	ifstream fileToRead;
	string data;

	system("cls");
	fileToRead.open(fileName);
	// validation checks
	if (fileToRead.is_open()) {
		// displaying the information
		while (getline(fileToRead, data)) {
			cout << data << endl;
		}
		cout << "\n\t";
	}
	fileToRead.close();
}

void createLists(string fileName) {	// Task 3: Read and Store Data from a File
	// declaring local variable
	ifstream fileToRead;
	string line;

	// reset the global variable to remove any previous data
	tallyData.clear();

	fileToRead.open(fileName);
	cout << "\n   Data loading from " << fileName << endl; 
	// validation checks
	if (fileToRead.is_open()) {
		// reading and storing data in tallyData
		while (!fileToRead.eof()) {
			getline(fileToRead, line);
			tallyData.push_back(line);
		}
		cout << "\tFile found...proceeding to load data.\n";
		cout << "\tLoading done...\n\t";
	}
	else {
		cout << "   File Not Found.\n\n\t";
	}
	fileToRead.close();
}

string generateTable() { // Task 4: Generate and Display a Dice Tally Table
	// declaring local variables
	int numRolls = rollsRequired * 10;

	// initialise or reset tallyResults
	for (int i = 0; i < MAX_SUM_OF_TWO_DICE; i++) {
		tallyResults[i] = 0;
	}

	// random generation of dice according to input in parameters
	while (numRolls > 0) {
		int generatedDice1 = rand() % 6 + 1;
		int generatedDice2;
		int sumOfTwoDice;

		// when user only picks one dice
		if (diceToRoll == 1) {
			tallyResults[generatedDice1]++;
		}
		// when user picks two dices
		else if (diceToRoll == 2) {
			generatedDice2 = rand() % 6 + 1;
			sumOfTwoDice = generatedDice1 + generatedDice2;
			tallyResults[sumOfTwoDice]++;
		}
		numRolls--;
	}

	return displayTable();
}

string displayTable() {
	string retVal = " You rolled " + to_string(diceToRoll) + " dice " + to_string(rollsRequired*10) + " times.\n" + string(43, '~') + "\n";

	// transforming the tallyResults into a string format
	for (int i = 0; i < MAX_SUM_OF_TWO_DICE; i++) {
		if (tallyResults[i] != 0) {
			retVal += to_string(i) + ": " + string(tallyResults[i], '*') + "\n";
		}
	}
	return retVal;
}

void saveData(string fileName, string currentTable) { // Task 5: Save a Dice Table to a File
	// declare local variables
	string userInput;
	ofstream fileToWrite(fileName, ios::app);

	// saving the data into the file
	if (fileToWrite.is_open()) {
		fileToWrite << currentTable;
		cout << "\tThese statistics are now saved.\n\t";
	}
	else {
		cout << "\n File Not Found.\n\t";
	}
	fileToWrite.close();
}

void loadData(string fileName) { // Task 6: Load Saved Dice Tables from a File
	// load the data into tallyData
	createLists(fileName);
	system("pause");
	system("cls");

	// display saved data in tallyData
	for (int i = 0; i < tallyData.size(); i++) {
		cout << tallyData[i]<< endl;
	}
}
