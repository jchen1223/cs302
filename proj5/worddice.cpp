// Project 5 - Word Dice
// Name: Aidan Feyerherm and Jeffrey Chen
// Takes an input of dice with letters, checks a list of
// words to see if the dice can make those words using network flow
// and Edmond Karp's algorithm.
// Last updated: 11/7/2024

#include <cstdio>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

class Node {
public:
  int id;
  vector<int> booleans;
  set<int> adj;   // Using set so there are no duplicate edges.
  Node *backedge; // Backwards edge; the node we "came" from.
  int dist;       // Essentially the original
};

// A double ended queue is used for Edmonds-Karp algorithm to find the
// augmenting path
class Graph {
public:
  Graph(vector<string>);
  ~Graph();
  deque<int> q;
  vector<pair<int, int>> path; // Stores the augmenting path found by BFS
  vector<Node *> nodes;
  void reset();
  void makegraph(string);
  void findpath();
  void adjust();
  void makepath();
  vector<string> dice;
};

// Sets the dice vector equal to the given vector
Graph::Graph(vector<string> s1) {
  size_t i, j;
  Node *n;

  dice = s1;

  // Resize the node list, 2 extra nodes for source and sink.
  nodes.resize((2 * dice.size()) + 2);

  // Initialize all nodes
  for (i = 0; i < nodes.size(); i++) {
    n = new Node;
    if (i == 0 || i == nodes.size() - 1)
      n->booleans.resize(256, 1);
    else
      n->booleans.resize(256, 0);
    n->id = i;
    n->dist = -1;
    n->backedge = NULL; // No backedge initally.
    nodes[i] = n;       // Add the nodes to the graph.
  }

  // Set the indices of the boolean vector to true if the die contains that
  // letter.
  // Iterates through all the dices
  for (i = 0; i < dice.size(); i++) {
    // Iterates through the specific dice letters.
    for (j = 0; j < dice[i].size(); j++) {
      if (nodes[i + 1]->booleans[dice[i][j]] == 0) {
        nodes[i + 1]->booleans[dice[i][j]] = 1;
      }
    }
  }

  // Connect source node (index 0) to the dice nodes (index 1 to dice.size())
  for (i = 1; i < (1 + dice.size()); i++) {
    // Add an edge from source to each die node
    nodes[0]->adj.insert(i);
  }
  for (i = 1 + dice.size(); i < nodes.size() - 1; i++) {
    nodes[i]->adj.insert(nodes.size() - 1);
  }
}

Graph::~Graph() {
  // Deletes all nodes and clear the vectors.
  size_t i;
  for (i = 0; i < nodes.size(); i++) {
    delete nodes[i];
  }
  nodes.clear();
}

void Graph::makegraph(string word) {
  size_t i, j;

  // Can't spell word if there are more words than dices.
  if (word.size() > dice.size()) {
    cout << "Cannot spell " << word << endl;
    return;
  }

  // Adds edges from dice to a letter in the word if the die contains that
  // letter
  for (i = 1; i < (1 + dice.size()); i++) {
    for (j = 0; j < word.size(); j++) {
      if (nodes[i]->booleans[word[j]] == 1) {
        nodes[i]->adj.insert(j + (1 + dice.size()));
      }
    }
  }
}

// Resets the graph to its initial state (before processing each word).
void Graph::reset() {
  size_t i;

  // Clears all existing nodes
  for (i = 0; i < nodes.size(); i++) {
    nodes[i]->adj.clear();
    nodes[i]->backedge = NULL;
    nodes[i]->dist = -1;
  }

  // Readds the dice nodes
  // Basically connects the source node to the dice nodes again.
  for (i = 1; i < (1 + dice.size()); i++) {
    nodes[0]->adj.insert(i);
  }

  // Reconnect dice nodes to sink node.
  for (i = 1 + dice.size(); i < nodes.size() - 1; i++) {
    nodes[i]->adj.insert(nodes.size() - 1);
  }
}

// Implements BFS to find an augmenting path
void Graph::findpath() {
  Node *n;
  set<int>::iterator sit;

  // BFS
  // Continue until the queue is empty.
  while (q.size() != 0) {
    n = nodes[*(q.begin())]; // Get the first node in the queue.
    q.pop_front();           // Pop it

    // Explore the adjacent nodes
    for (sit = n->adj.begin(); sit != n->adj.end(); sit++) {
      // Check if the node has been visited.
      if (nodes[(*sit)]->dist == -1) {

        // If it hasn't been visited then,
        // Set the distance
        // Set the backedge for path reconstruction
        // Then finally add the adjacent node to the queue.
        nodes[(*sit)]->dist = 1 + n->dist;
        nodes[(*sit)]->backedge = n;
        q.push_back((*sit));
      }
    }
  }
}

// Constructs the augmenting path found by BFS.
void Graph::makepath() {
  Node *n;
  n = nodes[nodes.size() - 1]; // Start from the sink node.
  // Trace back from the sink nodes using the backedges.
  while (n->backedge != NULL) {
    // Stores the edge in the path.
    path.push_back(make_pair(n->id, n->backedge->id));
    n = n->backedge;
  }
}

// Implements the network flow calculations.
// Updates the graph's flow

// I.e. modify the graph after an augmenting path has been found
// The purpose of the adjust() function is to get rid of the foward edge
// and have the reverse edge be the way to tell the
// iterator, or BFS, to go back and to find a different path.
void Graph::adjust() {
  size_t i;
  Node *n;
  set<int>::iterator sit;

  // For each edge in the augmenting path
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
  size_t i, j;
  size_t count;
  ifstream file1, file2;
  string line;
  Graph *g;
  vector<string> dice, words;
  set<int>::iterator sit; // Traverses adjacency list
  count = 0;

  // Opens the dice.txt file and stores the dices
  file1.open(argv[1]);
  while (getline(file1, line)) {
    dice.push_back(line);
  }

  // Opens the word.txt file and stores the words.
  file2.open(argv[2]);
  while (getline(file2, line)) {
    words.push_back(line);
  }

  file1.close();
  file2.close();
  g = new Graph(dice);

  // The words vector is traversed and the graph is updated for each word.
  for (i = 0; i < words.size(); i++) {
    // Build the graph for the current word
    // Set the source node's distance to 0.
    // Add the source node to the queue.
    // Find an augmenting path.
    g->makegraph(words[i]);
    g->nodes[0]->dist = 0;
    g->q.push_back(0);
    g->findpath();

    // For the while loop,
    // We use BFS to find an augmenting path
    // Then store the augmenting path
    // Then we use adjust() to remove the edges used and
    // add backedges to tell the next BFS iteration that they cannot
    // use that node again.
    // Next, we reset the graph, and BFS is run again to find the next
    // augmenting path. This repeats until the word is fully matched or no more
    // augmenting paths are found.

    // Try to find enough paths to spell the word.
    while (g->nodes[g->nodes.size() - 1]->backedge != NULL &&
           count < words[i].size()) {
      g->makepath();   // Construct the augmenting path found by BFS.
      g->adjust();     // Adjust the graph (remove used edges and reverse them).
      g->path.clear(); // Clear the path vector for the next iteration.

      // Reset all nodes' backedges and distances in preparation for the next
      // BFS.
      for (j = 0; j < g->nodes.size(); j++) {
        g->nodes[j]->backedge = NULL;
        g->nodes[j]->dist = -1;
      }

      // Re push the source node and prepare to restart the BFS again.
      g->nodes[0]->dist = 0;
      g->q.push_back(0);
      g->findpath();
      count++; // Increment the count of letters successfully matched.
    }

    // After finding all the augmenting paths, check if the word was fully
    // matched.
    if (count == words[i].size()) {

      // If the word was successfully spelled, print the result
      for (j = 0; j < words[i].size(); j++) {
        // Get the adjacency list of the letter node.
        sit = g->nodes[j + (1 + dice.size())]->adj.begin();
        if (j == words[i].size() - 1) {
          cout << (*sit) - 1 << ": ";
        } else {
          cout << (*sit) - 1 << ",";
        }
      }
      cout << words[i] << endl;
    } else {
      // If not all letters were matched, print that the word cannot be spelled.
      cout << "Cannot spell " << words[i] << endl;
    }

    /* The graph and count are reset to prep for the next word call. */
    g->reset();
    count = 0;
  }
  return 0;
}
