#pragma once
#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

// print an invalid message on console
void invalid_message() {
	cout << "Invalid choice! Press any key to try again...";
	_getch(); // wait for user to press a key
	cout << endl << endl;
}

// get user input by ignoring new line and empty line
string get_input() {
	string input;

	do { // verifying correct input
		getline(cin, input);

		if (input == "x" || input == "X") {
			cout << "Exiting..." << endl;
			_getch();
			exit(1);
		}
	} while (input == "\n" || input == "");

	return input;
}

// verifies if the user input was indeed an integer
bool verify_input(int& ret) {
	try {
		ret = stoi(get_input());
	}
	catch (exception e) { // invalid input
		invalid_message();
		return false;
	}

	return true;
}