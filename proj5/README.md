### Name: Jeffrey Chen and Aidan Feyerherm

### Contributions:
- Jeffrey Chen:
- Wrote adjust()
- Wrote ~Graph(); the destructor
- Reviewed the code written
- Wrote README.md and the report

- Aidan Feyerherm:
- Set up the classes
- Wrote main()
- Wrote Graph(); the constructor
- Wrote makepath(); the BFS
- Wrote reset()
- Wrote findpath()

### Questionaire:
- What is the complexity?
- The time complexity is O(W * (V + E) * V^3) which can be simplified to O(W * V^4).
- The W is the number of Words, the V is the number of vertices/nodes, and the E is the number of edges.
- For each word, we run the program, so that includes W, then for each word we need to constantly call BFS which is O(V+E), then after we call BFS we need to use the makepath() and adjust() functions which both are O(V), however, toogether they are O(V^2). Then we have one final for loop to reset the backedges which another O(V) so thus it would be O(V^3) once we account everything. Then we reset the loop with another BFS iteration, however, that is already included in the beginning and thus our implementation is O(W * (V+E) * V^3). However, we can simplify this to O(W * V^4).


