// Project 5 - Word Dice
// Takes an input of dice with letters, checks a list of
// words to see if the dice can make those words
// Last updated: 11/7/2024

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <deque>
using namespace std;

class Node {
public:
	int id;
	vector <int> booleans;
	set <int> adj;
	Node *backedge;
	int dist;

};

// A double ended queue is used for Edmonds-Karp algorithm to find the augmenting path 
class Graph {
public:
	Graph(vector <string>);
~Graph();
	deque <int> q;
	vector <pair<int,int> > path;
	vector <Node *> nodes;
	void reset();
	void makegraph(string);
	void findpath();
	void adjust();
	void  makepath();
	vector <string> dice;

};

// Sets the dice vector equal to the given vector 
Graph::Graph(vector <string> s1) {
	int i, j;
	Node *n;

	dice = s1;
	nodes.resize((2*dice.size())+2);

	// Initialize all nodes
	for (i = 0; i < nodes.size(); i++) {
		n = new Node;
		if (i == 0 || i == nodes.size()-1) 
			n->booleans.resize(256, 1);
		else
			n->booleans.resize(256, 0);
		n->id = i;
		n->dist = -1;
		n->backedge = NULL;
		nodes[i] = n;
	}

	// Set the indices of the boolean vector to true if the die contains that letter.
	for (i = 0; i < dice.size(); i++) {
		for (j = 0; j < dice[i].size(); j++) {
			if (nodes[i+1]->booleans[dice[i][j]] == 0) {
				nodes[i+1]->booleans[dice[i][j]] = 1;
			}
		}
	}

	for (i = 1; i < (1 + dice.size()); i++) {
		nodes[0]->adj.insert(i);
	}
	for (i = 1 + dice.size(); i < nodes.size()-1; i++) {
		nodes[i]->adj.insert(nodes.size()-1);
	}
}

Graph::~Graph() {
	int i;
	for (i = 0; i < nodes.size(); i++) {
		delete nodes[i];
	}
	nodes.clear();
}

void Graph::makegraph(string word) {
	int i, j;

	if (word.size() > dice.size()) {
		cout << "Cannot spell " << word << endl;
		return;
	}

	// Adds edges from dice to a letter in the word if the die contains that letter
	for (i = 1; i < (1 + dice.size()); i++) {
		for (j = 0; j < word.size(); j++) {
			if (nodes[i]->booleans[word[j]] == 1) {
				nodes[i]->adj.insert(j + (1 + dice.size()));
			}
		}
	}
}

void Graph::reset() {
	int i;

	for (i = 0; i < nodes.size(); i++) {
		nodes[i]->adj.clear();
		nodes[i]->backedge = NULL;
		nodes[i]->dist = -1;
	}

	for (i = 1; i < (1 + dice.size()); i++) {
		nodes[0]->adj.insert(i);
	}
	for (i = 1 + dice.size(); i < nodes.size()-1; i++) {
		nodes[i]->adj.insert(nodes.size()-1);
	}
}

void Graph::findpath() {
	int i;
	Node *n;
	set <int>::iterator sit;

	// Continue until the queue is empty. 
	while(q.size() != 0) {
		n = nodes[*(q.begin())];
		q.pop_front();
		for(sit = n->adj.begin(); sit != n->adj.end(); sit++) {
			if (nodes[(*sit)]->dist == -1) {
				nodes[(*sit)]->dist = 1 + n->dist;
				nodes[(*sit)]->backedge = n;
				q.push_back((*sit));
			}
		}
	}
}

void Graph::makepath() {
	int j;
	Node *n;
	n = nodes[nodes.size()-1];
	while (n->backedge != NULL) {
		path.push_back(make_pair(n->id, n->backedge->id));
		n = n->backedge;
	}
}

// Implements the network flow calculations.
void Graph::adjust() {
	int i, j;
	Node *n;
	set <int>::iterator sit;

	for (i = 0; i < path.size(); i++) {
		n = nodes[path[i].second];
		sit = n->adj.find(path[i].first);
		if (sit != n->adj.end()) {
			n->adj.erase(sit);
		}
		nodes[path[i].first]->adj.insert(path[i].second);
	}
}

int main(int argc, char *argv[]) {
	int i, j;						
	int count;				
	ifstream file1, file2;	
	string line;			
	Graph *g;				
	vector <string> dice, words;	
	set <int>::iterator sit;	// Traverses adjacency list
	count = 0;

	file1.open(argv[1]);
	while (getline(file1, line)) {
		dice.push_back(line);
	}
	file2.open(argv[2]);
	while (getline(file2, line)) {
		words.push_back(line);
	}
	file1.close();
	file2.close();
	g = new Graph(dice);

	// The words vector is traversed and the graph is updated for each word.
	for (i = 0; i < words.size(); i++) {
		g->makegraph(words[i]);
		g->nodes[0]->dist = 0;
		g->q.push_back(0);
		g->findpath();

		while(g->nodes[g->nodes.size()-1]->backedge != NULL  && count < words[i].size()) {
			g->makepath();
			g->adjust();
			g->path.clear();
			for (j = 0; j < g->nodes.size(); j++) {
				g->nodes[j]->backedge = NULL;
				g->nodes[j]->dist = -1;
			}
			g->nodes[0]->dist = 0;
			g->q.push_back(0);
			g->findpath();
			count++;
		}

		if (count == words[i].size()) {
			for(j = 0; j < words[i].size(); j++) {
				sit = g->nodes[j + (1 + dice.size())]->adj.begin();
				if (j == words[i].size() - 1) {
					cout << (*sit) - 1 << ": ";
				}
				else {
					cout << (*sit) - 1 << ",";
				}
			}
			cout << words[i] << endl;
		}
		else {
			cout << "Cannot spell " << words[i] << endl;
		}

		/* The graph and count are reset to prep for the next word call. */
		g->reset();
		count = 0;
	}
	return 0;
}
