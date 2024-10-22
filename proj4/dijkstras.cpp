// Project 4 - Path Finding
// Aidan Feyerherm, Jeffrey Chen
// Helps a theoretical runner traverse a map with the
// lowest possible cost.
// Last updated: 10/22/2024

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm>
using namespace std;

struct Node {
    int row, col, cost;
    Node(int r, int c, int cst) : row(r), col(c), cost(cst) {}
};

struct CompareNode {
    bool operator()(const Node& n1, const Node& n2) {
        return n1.cost > n2.cost;
    }
};

class Dijkstra {
private:
    vector<vector<char>> map;
    unordered_map<char, int> tileCosts;
    int rows, cols;
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

public:
    void readInput() {
        int tilesN;
        cin >> tilesN;

        for (int i = 0; i < tilesN; i++) {
            char tileName;
            int tileCost;
            cin >> tileName >> tileCost;
            tileCosts[tileName] = tileCost;
        }

        cin >> rows >> cols;
        map.resize(rows, vector<char>(cols));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> map[i][j];
            }
        }
    }

    vector<pair<int, int>> findShortestPath(int startRow, int startCol, int endRow, int endCol) {
        vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
        vector<vector<pair<int, int>>> prev(rows, vector<pair<int, int>>(cols, {-1, -1}));
        priority_queue<Node, vector<Node>, CompareNode> pq;

        dist[startRow][startCol] = 0;
        pq.push(Node(startRow, startCol, 0));

        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();

            if (current.row == endRow && current.col == endCol) {
                break;
            }

            for (const auto& dir : directions) {
                int newRow = current.row + dir.first;
                int newCol = current.col + dir.second;

                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                    int newCost = current.cost + tileCosts[map[current.row][current.col]];

                    if (newCost < dist[newRow][newCol]) {
                        dist[newRow][newCol] = newCost;
                        prev[newRow][newCol] = {current.row, current.col};
                        pq.push(Node(newRow, newCol, newCost));
                    }
                }
            }
        }

        vector<pair<int, int>> path;
        int currentRow = endRow, currentCol = endCol;

        while (currentRow != -1 && currentCol != -1) {
            path.push_back({currentRow, currentCol});
            int prevRow = prev[currentRow][currentCol].first;
            int prevCol = prev[currentRow][currentCol].second;
            currentRow = prevRow;
            currentCol = prevCol;
        }

        reverse(path.begin(), path.end());
        return path;
    }

    void printResult(const vector<pair<int, int>>& path) {
        if (path.empty() || path[0].first == -1) {
            cout << "No path found" << endl;
            return;
        }

        int totalCost = 0;
        for (size_t i = 0; i < path.size() - 1; i++) {
            int row = path[i].first;
            int col = path[i].second;
            totalCost += tileCosts[map[row][col]];
        }

        cout << totalCost << endl;
        for (const auto& p : path) {
            int row = p.first;
            int col = p.second;
            cout << row << " " << col << endl;
        }
    }
};

int main() {
    Dijkstra dijkstra;
    dijkstra.readInput();

    int startRow, startCol, endRow, endCol;
    cin >> startRow >> startCol >> endRow >> endCol;

    vector<pair<int, int>> shortestPath = dijkstra.findShortestPath(startRow, startCol, endRow, endCol);
    dijkstra.printResult(shortestPath);

    return 0;
}
