Jeffrey Chen, Aidan Feyerherm
- Project 04: Path Finding
# Benchmark

| N | Elapsed Time | Memory Usage |
|-|-|-|
| 10 | 0.00 sec | 85,538 bytes |
| 20 | 0.00 sec | 91,568 bytes |
| 50 | 0.00 sec | 125,002 bytes |
| 100 | 0.01 sec | 232,896 bytes |
| 200 | 0.02 sec | 643,684 bytes |
| 500 | 0.15 sec | 3,440,144 bytes |
| 1000 | 0.60 sec | 13,298,180 bytes |

1. How did you represent the map as a graph?
- In our implementation of Dihkstra's Algorithm, the map is represented as a grid (2d vector) and each cell corresponds to a vertex in the graph. The edge between each vertex is determined by their adjacency or in other words, their neighbors. For example, up, down, left, and right.

2. What is complexity of your implementation of Dijkstra's Algorithm?
- O(V log V)
- This is becaause we have our initialization of the board which is O(V), then we have priority queue operations like top and pop which can be O(log V). Finally, we have the edges which for each vertex, we can explore up to potentially 4 edges (or neighbors). However, since the number of egdes is approximately the same as V O(E) is approximately the same as O(V).

3. How well does your implementation scale?
- Of course as the board grows, it is obvious that the time and space complexity will also grow. However, the time doesn't grow as much as much as the memory allocated usage did, as the time needed was still quite considerably fast. Meanwhile the memory allocated grows significantly. This is perhaps because in our implementation there is a priority queue, a map, multiple vectors, and lastly 2d vectors being used.
