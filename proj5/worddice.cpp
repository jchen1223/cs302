// Aidan Feyerherm
// Project 5 - Word Dice
// Takes an input of dice with letters, checks a list of
// words to see if the dice can make those words
// Last updated: 11/7/2024

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

const int SOURCE = 0;
const int SINK = 1;

// Graph class to represent the flow network
class Graph {
private:
	int V;
	vector<vector<int>> adj;
	vector<vector<int>> capacity;

public:
	Graph(int vertices) : V(vertices) {
		adj.resize(V);
		capacity.resize(V, vector<int>(V, 0));
	}

	// Add an edge to the graph
	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
		capacity[u][v] = 1;
	}

	// Breadth-First Search to find augmenting paths
	bool bfs(vector<int>& parent) {
		vector<bool> visited(V, false);
		queue<int> q;
		q.push(SOURCE);
		visited[SOURCE] = true;
		parent[SOURCE] = -1;

		while (!q.empty()) {
			int u = q.front();
			q.pop();

			for (int v : adj[u]) {
				if (!visited[v] && capacity[u][v] > 0) {
					q.push(v);
					parent[v] = u;
					visited[v] = true;
				}
			}
		}

		return visited[SINK];
	}

	// Edmonds-Karp algorithm for maximum flow
	int maxFlow() {
		vector<int> parent(V);
		int max_flow = 0;

		while (bfs(parent)) {
			int path_flow = INT_MAX;
			for (int v = SINK; v != SOURCE; v = parent[v]) {
				int u = parent[v];
				path_flow = min(path_flow, capacity[u][v]);
			}

			for (int v = SINK; v != SOURCE; v = parent[v]) {
				int u = parent[v];
				capacity[u][v] -= path_flow;
				capacity[v][u] += path_flow;
			}

			max_flow += path_flow;
		}

		return max_flow;
	}
};

// Read dice from input file
vector<string> readDice(const string& filename) {
	vector<string> dice;
	ifstream file(filename);
	string die;
	while (file >> die) {
		dice.push_back(die);
	}
	return dice;
}

// Read words from input file
vector<string> readWords(const string& filename) {
	vector<string> words;
	ifstream file(filename);
	string word;
	while (file >> word) {
		words.push_back(word);
	}
	return words;
}

// Check if a word can be spelled using the given dice
bool canSpellWord(const vector<string>& dice, const string& word) {
	size_t V = 2 + dice.size() + word.length();
	Graph g(static_cast<int>(V));

	// Add edges from source to dice
	for (size_t i = 0; i < dice.size(); i++) {
		g.addEdge(SOURCE, static_cast<int>(i + 2));
	}

	// Add edges from letters to sink
	for (size_t i = 0; i < word.length(); i++) {
		g.addEdge(static_cast<int>(i + dice.size() + 2), SINK);
	}

	// Add edges from dice to letters
	for (size_t i = 0; i < dice.size(); i++) {
		for (size_t j = 0; j < word.length(); j++) {
			if (dice[i].find(word[j]) != string::npos) {
				g.addEdge(static_cast<int>(i + 2), static_cast<int>(j + dice.size() + 2));
			}
		}
	}

	// Check if maximum flow equals word length
	return g.maxFlow() == static_cast<int>(word.length());
}

// Get the order of dice used to spell a word
vector<int> getDiceOrder(const vector<string>& dice, const string& word) {
	vector<int> order;
	vector<bool> used(dice.size(), false);

	for (char c : word) {
		for (size_t i = 0; i < dice.size(); i++) {
			if (!used[i] && dice[i].find(c) != string::npos) {
				order.push_back(static_cast<int>(i));
				used[i] = true;
				break;
			}
		}
	}

	return order;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <dice_file> <words_file>" << endl;
		return 1;
	}

	// Read input files
	vector<string> dice = readDice(argv[1]);
	vector<string> words = readWords(argv[2]);

	// Process each word
	for (const string& word : words) {
		if (canSpellWord(dice, word)) {
			vector<int> order = getDiceOrder(dice, word);
			// Output the dice order and word
			for (size_t i = 0; i < order.size(); i++) {
				cout << order[i];
				if (i < order.size() - 1) cout << ",";
			}
			cout << ": " << word << endl;
		} else {
			cout << "Cannot spell " << word << endl;
		}
	}

	return 0;
}
