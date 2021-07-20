#define DEBUG true

#include <iostream>
#include <conio.h>
#include <string>
#include "Util.h"
#include "App.h"

using namespace std;

class Program {

private:
	App app;

public:
	
	Program() {
		// if data set wasn't loaded in the app then return
		if (!app.has_dataset_loaded()) {
			cout << "Exiting..." << endl;
			_getch();
			exit(1);
		}
	}

	App& get_app() {
		return app;
	}

	void intra_city() {
		string city, town_1, town_2;
		int ch;

		cout << "Enter city: ";
		city = get_input();

		cout << "Enter the source town: ";
		town_1 = get_input();

		cout << "Enter the destination town: ";
		town_2 = get_input();

		// repeat unless the user enter the proper input
		bool verified_choice = false; 

		do {
			cout << "Please choose, " << endl;
			cout << "1. Get path with shortest time" << endl;
			cout << "2. Get path with shortest distance" << endl;
			cout << "3. Get both combined" << endl;
			cout << "Choice (1/2/3): ";

			if (!verify_input(ch)) {
				continue;
			}

			cout << endl;

			switch (ch) {
			case 1: // path by shortest time
				app.print_shortest_town_path(city, town_1, town_2, PATH::BY_TIME);
				break;

			case 2: // path by shortest distance
				app.print_shortest_town_path(city, town_1, town_2, PATH::BY_DISTANCE);
				break;

			case 3: // path by shortest distance and path by shortest time
				app.print_shortest_town_path(city, town_1, town_2, PATH::BY_TIME);
				cout << endl;
				app.print_shortest_town_path(city, town_1, town_2, PATH::BY_DISTANCE);
				break;

			default: // invalid user input
				invalid_message();
				continue;
			}

			verified_choice = true;
		} while (!verified_choice);
	}

	void inter_city() {
		string city_1, city_2, stop_city;
		char stop;
		int ch;

		cout << "Enter the source city: ";
		city_1 = get_input();

		cout << "Enter the destination city: ";
		city_2 = get_input();

		cout << "Press S to map path through a city or press any other key to continue...";
		stop = toupper(_getch());
		cout << endl;

		if (stop == 'S') {
			cout << "Enter the city which you would like to add along the path: ";
			stop_city = get_input();
		}

		// repeat unless the user enter the proper input
		bool verified_choice = false;

		do {
			cout << "Please choose, " << endl;
			cout << "1. Get path with shortest time" << endl;
			cout << "2. Get path with shortest distance" << endl;
			cout << "3. Get both combined" << endl;
			cout << "Choice (1/2/3): ";

			if (!verify_input(ch)) {
				continue;
			}

			cout << endl;

			switch (ch) {
			case 1: // path by shortest time
				if (stop == 'S') {
					app.print_shortest_city_path(city_1, city_2, stop_city, PATH::BY_TIME);
				}
				else {
					app.print_shortest_city_path(city_1, city_2, PATH::BY_TIME);
				}
				break;

			case 2: // path by shortest distance
				if (stop == 'S') {
					app.print_shortest_city_path(city_1, city_2, stop_city, PATH::BY_DISTANCE);
				}
				else {
					app.print_shortest_city_path(city_1, city_2, PATH::BY_DISTANCE);
				}
				break;

			case 3: // path by shortest distance and path by shortest time
				if (stop == 'S') {
					app.print_shortest_city_path(city_1, city_2, stop_city, PATH::BY_TIME);
					cout << endl;
					app.print_shortest_city_path(city_1, city_2, stop_city, PATH::BY_DISTANCE);
				}
				else {
					app.print_shortest_city_path(city_1, city_2, PATH::BY_TIME);
					cout << endl;
					app.print_shortest_city_path(city_1, city_2, PATH::BY_DISTANCE);
				}
				break;

			default: // invalid user input
				invalid_message();
				continue;
			}

			verified_choice = true;
		} while (!verified_choice);
	}

	void main_screen() {
		int ch;
		
		cout << "PATH MAPPER" << endl;
		cout << endl;
		cout << "To exit anywhere within the program, enter X" << endl;
		cout << endl;
		cout << "1. Intra-city" << endl;
		cout << "2. Inter-city" << endl;
		cout << endl;
		cout << "Choice (1/2): ";

		if (!verify_input(ch)) {
			main_screen();
			return;
		}

		cout << endl;

		switch (ch) {
		case 1: // intra city path finder
			intra_city();
			break;

		case 2: // inter city path finder
			inter_city();
			break;

		default: // invalid user input
			invalid_message();
			main_screen();
			return;
		}

		cout << endl;
	}
};

int main() {
	Program program;
	char exit;

	do {
		program.main_screen();

		cout << "Press X to exit or any other key to continue...";
		exit = _getch();
		cout << endl << endl;

	} while (toupper(exit) != 'X');

	//Edge e = program.get_app().get_cities().smallest_edge();

	//program.get_app().print_shortest_city_path("Rawalpindi", "Lahore", PATH::BY_DISTANCE); cout << endl;
	//program.get_app().print_shortest_city_path("Rawalpindi", "Karachi", "Chakwal", PATH::BY_DISTANCE); cout << endl;

	cout << "Exiting..." << endl;
	_getch();

	return 0;
}