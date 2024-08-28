Jeffrey Chen
Aidan Feyerherm

jchen1223
AFeyerherm224

https://github.com/jchen1223/cs302

g++ -o lib_info lib_info.cpp

We used helper functions to convert the time to strings to ints and back, and to remove the underscore and replace them with whitespace. Then using ifstream to connect to the file and sstringstream to parse the string into smaller variable strings. The logic behind the while loop is we read in the whole line and that would create a struct called Song that would hold the things we want, and then check if the song is under an artist and if not then create a new struct called Artist that would then hold it, then finally do the same process for album. We then used reference to be able to edit the structs and used maps to hold the structs. Finally, we loop through all the structs inside the map to print it out in the lexicographically format.
