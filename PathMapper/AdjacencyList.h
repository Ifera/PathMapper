#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <sstream>

#define INF 999999

using namespace std;

enum class PATH {
	BY_DISTANCE,
	BY_TIME
};

struct Edge {
	string current_vertex;
	string adjacent_vertex;
	int time;
	int distance;

	Edge() {
		time = 0;
		distance = 0;
	}

	Edge(string current_vertex, string adjacent_vertex, int time = 0, int distance = 0) {
		this->current_vertex = current_vertex;
		this->adjacent_vertex = adjacent_vertex;
		this->time = time;
		this->distance = distance;
	}

	bool operator==(const Edge& obj) {
		return current_vertex == obj.current_vertex && adjacent_vertex == obj.adjacent_vertex;
	}
};

struct Vertex {
	string data;
	list<Edge>* edges;

	Vertex() {
		edges = NULL;
	}

	Vertex(string data) {
		this->data = data;
		edges = NULL;
	}

	Vertex(const Vertex& cpy) {
		data = cpy.data;

		if (cpy.edges == NULL) {
			edges = NULL;
			return;
		}

		edges = new list<Edge>(*cpy.edges);
	}

	~Vertex() {
		if (edges != NULL) {
			delete edges;
		}
	}

	string get_data() {
		return data;
	}

	void set_data(string data) {
		this->data = data;
	}

	list<Edge>* get_edges() {
		if (edges == NULL) {
			edges = new list<Edge>();
		}

		return edges;
	}

	void set_edges(list<Edge>* edges) {
		this->edges = edges;
	}

	bool contains(Edge& edge) {
		for (auto edge_it = get_edges()->begin(); edge_it != get_edges()->end(); edge_it++) {
			if (edge == *edge_it) {
				return true;
			}
		}

		return false;
	}
};

// the templated class should be of type Vertex
template <typename T>
class AdjacencyList {

private:
	vector<T> graph;

	bool contains(vector<T> vec, string to_find) {
		for (auto vec_it = vec.begin(); vec_it != vec.end(); vec_it++) {
			if (vec_it->get_data() == to_find) {
				return true;
			}
		}

		return false;
	}

	// key -> vertex
	// value -> the shortest vertex used to approach the key
	string get_path(map<string, string>& path_map, string end) {
		stack<string> path;
		stringstream stream;

		while (path_map[end] != end) {
			path.push(end);
			end = path_map[end];
		}

		while (!path.empty()) {
			stream << " -> " << path.top();
			path.pop();
		}

		return stream.str();
	}

	// shortest_path will contain the shortest path found from start to end
	// value will be the time or distance, based on path_algo
	// ext will be the extra data, it will contain time if path_algo wanted distance and vice versa
	bool get_shortest_path(string start, string end, enum PATH path_algo, string& shortest_path, int& value, int &ext) {
		if (is_empty()) {
			cout << "Error: The graph is empty" << endl;
			return false;
		}

		if (!is_reachable(start, end)) {
			cout << "Error: There is no path from " << start << " to " << end << endl;
			return false;
		}

		map<string, int> weight; // min time/distance based on path_algo
		map<string, int> extra; // would store time or distance, for the purpose of ext
		map<string, bool> visited;
		map<string, string> path;

		// mark all vertices as unvisited and give the highest weight
		for (auto graph_it = graph.begin(); graph_it != graph.end(); graph_it++) {
			weight[graph_it->get_data()] = INF;
			extra[graph_it->get_data()] = INF;
			visited[graph_it->get_data()] = false;
		}

		// give the source/start vertex a weight of zero
		weight[start] = 0;
		extra[start] = 0;
		path[start] = start;

		string ver, edge;
		typename vector<T>::iterator ver_it;
		get_vertex(start, ver_it);

		while (true) {
			ver = ver_it->get_data();

			if (ver == end) {
				break;
			}

			visited[ver] = true;

			for (auto edge_it = ver_it->get_edges()->begin(); edge_it != ver_it->get_edges()->end(); edge_it++) {
				int w = INF, e = INF;
				edge = edge_it->adjacent_vertex;

				// either the path is to be found by shortest time taken or shortest distance
				if (path_algo == PATH::BY_TIME) {
					w = edge_it->time;
					e = edge_it->distance;
				}
				else {
					w = edge_it->distance;
					e = edge_it->time;
				}

				// update the weight only if the vertex/edge is not visited and the total sum 
				// of weight from source vertex to the edge is less than the current weight of edge
				if (!visited[edge] && weight[ver] + w < weight[edge]) {
					path[edge] = ver;
					weight[edge] = weight[ver] + w;
					extra[edge] = extra[ver] + e;
				}
			}

			string v, min_ver;
			int min = INF;

			// finding the smallest weight
			for (auto weight_it = weight.begin(); weight_it != weight.end(); weight_it++) {
				v = weight_it->first;

				if (!visited[v] && weight[v] <= min) {
					min = weight[v];
					min_ver = v;
				}
			}

			get_vertex(min_ver, ver_it);
		}

		shortest_path = get_path(path, end);
		value = weight[end];
		ext = extra[end];

		return true;
	}

	void print_extra_data(int value, int ext, enum PATH path_algo = PATH::BY_DISTANCE) {
		if (path_algo == PATH::BY_TIME) {
			int minutes = value % 60;
			int hours = value / 60;

			cout << "Total time taken: " << hours << " hours and " << minutes << " minutes (Distance: " << ext << " km)" << endl;
		}
		else {
			int minutes = ext % 60;
			int hours = ext / 60;

			cout << "Total distance covered: " << value << " km (Time: " << hours << " hours and " << minutes << " minutes)" << endl;
		}
	}

public:

	bool is_empty() {
		return graph.empty();
	}

	vector<T>& get_graph() {
		return graph;
	}

	int get_vertices() {
		if (is_empty()) {
			return 0;
		}

		return graph.size();
	}

	int get_edges() {
		if (is_empty()) {
			return 0;
		}

		int count = 0;

		for (auto ver : graph) {
			for (auto edge : *ver.get_edges()) {
				count++;
			}
		}

		return count / 2;
	}

	// returns whether vertex exists or not and a reference to the iterator
	bool get_vertex(string data, typename vector<T>::iterator& vertex_it) {
		vertex_it = graph.begin();

		for (; vertex_it != graph.end(); vertex_it++) {
			if (vertex_it->get_data() == data) {
				return true;
			}
		}

		return false;
	}

	bool insert_vertex(string val) {
		if (contains(graph, val)) { // vertex already exist
			return false;
		}

		graph.push_back(T(val));

		return true;
	}

	bool insert_vertex(T& ver) {
		if (contains(graph, ver.get_data())) { // vertex already exist
			return false;
		}

		graph.push_back(ver);

		return true;
	}
	
	Edge& get_smallest_edge() {
		Edge temp_edge("temp", "temp", INF, INF);

		for (auto vec_it = graph.begin(); vec_it != graph.end(); vec_it++) {
			for (auto edge_it = vec_it->get_edges()->begin(); edge_it != vec_it->get_edges()->end(); edge_it++) {
				if (edge_it->time < temp_edge.time && edge_it->distance < temp_edge.distance) {
					temp_edge = *edge_it;
				}
			}
		}

		return temp_edge;
	}

	bool insert_edge(string vertex_1, string vertex_2, int time = 0, int distance = 0) {
		typename vector<T>::iterator ver_1, ver_2;

		if (!get_vertex(vertex_1, ver_1)) { // vertex 1 not found
			if(DEBUG) cout << "Error: Unable to insert edge. Vertex: " << vertex_1 << " not found" << endl;
			return false;
		}

		if (!get_vertex(vertex_2, ver_2)) { // vertex 2 not found
			if (DEBUG) cout << "Error: Unable to insert edge. Vertex: " << vertex_2 << " not found" << endl;
			return false;
		}

		Edge edge_1(vertex_1, vertex_2, time, distance);

		// if it exists in one vertex then it will also exist in the other vertex
		if (ver_1->contains(edge_1)) {
			if (DEBUG) cout << "Error: Unable to insert edge. Edge between " << vertex_1 << " and " << vertex_2 << " already exists" << endl;
			return false;
		}

		ver_1->get_edges()->push_back(edge_1);
		ver_2->get_edges()->push_back(Edge(vertex_2, vertex_1, time, distance));

		return true;
	}

	bool is_adjacent(string vertex_1, string vertex_2) {
		if (is_empty()) {
			return false;
		}

		typename vector<T>::iterator ver;

		// vertex isnt adjacent since it doesnt exist
		if (!get_vertex(vertex_1, ver)) {
			return false;
		}

		for (auto edge_it = ver->get_edges()->begin(); edge_it != ver->get_edges()->end(); edge_it++) {
			if (edge_it->adjacent_vertex == vertex_2) {
				return true;
			}
		}

		return false;
	}

	bool delete_edge(string vertex_1, string vertex_2) {
		if (is_empty()) {
			return false;
		}

		if (!is_adjacent(vertex_1, vertex_2)) { // no edge exist
			return false;
		}

		typename vector<T>::iterator ver_1, ver_2;

		get_vertex(vertex_1, ver_1);
		get_vertex(vertex_2, ver_2);

		// delete edge of vertex 2 from vertex 1
		for (auto edge_it_1 = ver_1->get_edges()->begin(); edge_it_1 != ver_1->get_edges()->end(); edge_it_1++) {
			if (edge_it_1->adjacent_vertex == vertex_2) {
				edge_it_1 = ver_1->get_edges()->erase(edge_it_1);
				break;
			}
		}

		// delete edge of vertex 1 from vertex 2
		for (auto edge_it_2 = ver_2->get_edges()->begin(); edge_it_2 != ver_2->get_edges()->end(); edge_it_2++) {
			if (edge_it_2->adjacent_vertex == vertex_1) {
				edge_it_2 = ver_2->get_edges()->erase(edge_it_2);
				break;
			}
		}

		return true;
	}

	// delete all edges of the vertex
	bool delete_edges(string ver) {
		if (is_empty()) {
			return false;
		}

		for (auto graph_it = graph.begin(); graph_it != graph.end(); graph_it++) {
			for (auto edge_it = graph_it->get_edges()->begin(); edge_it != graph_it->get_edges()->end(); edge_it++) {
				if (edge_it->adjacent_vertex == ver) {
					edge_it = graph_it->get_edges()->erase(edge_it);
					break;
				}
			}
		}

		return true;
	}

	bool delete_vertex(string ver) {
		if (is_empty()) {
			return false;
		}

		delete_edges(ver); // delete the vertex from all the edges

		for (auto it = graph.begin(); it != graph.end(); it++) {
			if (it->get_data() == ver) {
				it = graph.erase(it);
				break;
			}
		}

		return true;
	}

	// returns the index of where the vertex is located or returns -1 if not found
	int search(string ver) {
		if (is_empty()) {
			return false;
		}

		typename vector<T>::iterator _ver;

		if (!get_vertex(ver, _ver)) { // vertex doesnt exist
			return -1;
		}

		return _ver - graph.begin();
	}

	// check if there exists a path from vertex 1 to vertex 2
	bool is_reachable(string vertex_1, string vertex_2) {
		if (is_empty()) {
			return false;
		}

		if (vertex_1 == vertex_2) { // base case
			return true;
		}

		string data = vertex_1;
		vector<T> visited;
		queue<string> queue;

		queue.push(data);

		while (!queue.empty()) {
			data = queue.front();
			queue.pop();

			// the vertex was visited
			if (contains(visited, data)) {
				continue;
			}

			typename vector<T>::iterator ver_it;

			if (!get_vertex(data, ver_it)) {
				continue;
			}

			for (auto edge_it = ver_it->get_edges()->begin(); edge_it != ver_it->get_edges()->end(); edge_it++) {
				if (edge_it->adjacent_vertex == vertex_2) {
					return true;
				}

				queue.push(edge_it->adjacent_vertex);
			}

			visited.push_back(*ver_it);
		}

		return false;
	}

	// find the shortest path and the path length by using dijkistra algorithm
	void print_shortest_path(string start, string end, enum PATH path_algo = PATH::BY_DISTANCE) {
		string path;
		int value, ext;

		if (!get_shortest_path(start, end, path_algo, path, value, ext)) return;
		
		cout << "Shortest path based on " << (path_algo == PATH::BY_TIME ? "time taken" : "distance") << ", from " << start << " to " << end << " is: " << endl;
		cout << start << path << endl;

		print_extra_data(value, ext, path_algo);
	}

	void print_shortest_path(string start, string end, string stop, enum PATH path_algo = PATH::BY_DISTANCE) {
		string path_1, path_2;
		int value_1, value_2, ext_1, ext_2;

		if (!get_shortest_path(start, stop, path_algo, path_1, value_1, ext_1)) return;
		if (!get_shortest_path(stop, end, path_algo, path_2, value_2, ext_2)) return;

		cout << "Shortest path based on " << (path_algo == PATH::BY_TIME ? "time taken" : "distance") << ", from " << start << " to " << end << " via " << stop << ", is: " << endl;
		cout << start << path_1 << path_2 << endl;

		print_extra_data(value_1 + value_2, ext_1 + ext_2, path_algo);
	}

	// overloading the subscript operator
	T& operator[](const int i) {
		return graph[i];
	}
};