#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "nlohmann/json.hpp"
#include "AdjacencyList.h"

using namespace std;
using json = nlohmann::json;

struct City : public Vertex {

	AdjacencyList<Vertex> towns;

	City() : Vertex() {}

	City(string data) : Vertex(data) {}

	void set_towns(AdjacencyList<Vertex>& towns) {
		this->towns = towns;
	}

	AdjacencyList<Vertex>& get_towns() {
		return towns;
	}
};

class App {

private:
	AdjacencyList<City> cities;
	bool dataset_loaded = false;

public:

	App() {
		if (dataset_loaded) {
			cout << "Warn: App has already been loaded with the dataset";
			return;
		}

		ifstream dataset_file("dataset.json");

		if (!dataset_file.is_open()) {
			cout << "Error: Unable to read dataset.json file" << endl;
			return;
		}

		try {
			// read the file in to the dataset object
			json dataset;
			dataset_file >> dataset;

			auto cities = dataset["cities"];
			auto city_links = dataset["links"];
			auto towns_data = dataset["towns"];

			for (string city : cities) {
				add_city(city);
			}

			for (auto city_link : city_links) {
				link_cities(city_link["city_1"], city_link["city_2"], city_link["time"], city_link["distance"]);
			}

			for (auto town_data : towns_data) {
				string city = town_data["city"];
				auto towns = town_data["towns"];
				auto town_links = town_data["links"];

				for (string town : towns) {
					add_town(city, town);
				}

				for (auto town_link : town_links) {
					link_city_towns(city, town_link["town_1"], town_link["town_2"], town_link["time"], town_link["distance"]);
				}
			}
			
			dataset_loaded = true;
		}
		catch (exception e) {
			cout << "Error: Something went wrong, please verify the dataset.json is correct" << endl;
			return;
		}
	}

	AdjacencyList<City>& get_cities() {
		return cities;
	}

	bool add_city(string city) {
		return cities.insert_vertex(city);
	}

	bool add_town(string city, string town) {
		vector<City>::iterator city_it;

		if (!cities.get_vertex(city, city_it)) {
			return false;
		}

		return city_it->towns.insert_vertex(town);
	}

	bool link_cities(string city_1, string city_2, int time = 0, int distance = 0) {
		return cities.insert_edge(city_1, city_2, time, distance);
	}

	bool link_city_towns(string city, string town_1, string town_2, int time = 0, int distance = 0) {
		vector<City>::iterator city_it;

		if (!cities.get_vertex(city, city_it)) {
			return false;
		}

		return city_it->towns.insert_edge(town_1, town_2, time, distance);
	}

	void print_shortest_city_path(string source, string destination, enum PATH path = PATH::BY_DISTANCE) {
		cities.print_shortest_path(source, destination, path);
	}

	void print_shortest_city_path(string source, string destination, string stop, enum PATH path = PATH::BY_DISTANCE) {
		cities.print_shortest_path(source, destination, stop, path);
	}

	void print_shortest_town_path(string city, string town_1, string town_2, enum PATH path = PATH::BY_DISTANCE) {
		vector<City>::iterator city_it;

		if (!cities.get_vertex(city, city_it)) {
			cout << "Error: Unable to find city: " << city << endl;
			return;
		}

		cout << "City: " << city << endl;
		city_it->towns.print_shortest_path(town_1, town_2, path);
	}

	bool has_dataset_loaded() {
		return dataset_loaded;
	}
};