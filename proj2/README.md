Jeffrey Chen, Aidan Feyerherm, Joey DiSalvo, Cristian Frutus
- Project 02: Sorting List-Based Strings and Numbers
# Benchmark

| Mode and Size | Elapsed Time and Memory Consumption |
|------------------------------------|---------------------------------------------------------|
| STL 10 | .002 sec - 73,728 bytes | 
| STL 100 | .002 sec - 73,728 bytes | 
| STL 1000 | .002 sec - 146,296 bytes | 
| STL 10000 | .012 sec - 824,056 bytes | 
| STL 100000 | .106 sec - 6,979,064 bytes | 
| STL 1000000 | 1.336 sec - 64,859,128 bytes | 
| STL 10000000 | 14.98 sec - 748,516,344 bytes |
| - | - |
| QSort 10 | .002 sec - 82,400 bytes | 
| QSort 100 | .002 sec - 86,720 bytes | 
| QSort 1000 | .003 sec - 137,920 bytes | 
| QSort 10000 | .011 sec - 641,920 bytes | 
| QSort 100000 | .097 sec - 5,681,920 bytes | 
| QSort 1000000 | 1.120 sec - 56,081,920 bytes | 
| QSort 10000000 | 73.31 sec - 480,080,896 bytes |
| - | - |
| Merge 10 | .003 sec - 82,400 bytes | 
| Merge 100 | .002 sec - 86,720 bytes | 
| Merge 1000 | .003 sec - 129,920 bytes | 
| Merge 10000 | .011 sec - 561,920 bytes | 
| Merge 100000 | .100 sec - 4,881,920 bytes | 
| Merge 1000000 | 1.273 sec - 48,081,920 bytes | 
| Merge 10000000 | 16.123 sec - 480,081,920 bytes |
| - | - |
| Quick 10 | .002 sec - 82,400 bytes | 
| Quick 100 | .002 sec - 86,720 bytes | 
| Quick 1000 | .003 sec - 129,920 bytes | 
| Quick 10000 | .012 sec - 561,920 bytes | 
| Quick 100000 | .107 sec - 4,881,920 bytes | 
| Quick 1000000 | 1.755 sec - 48,081,920 bytes | 
| Quick 10000000 | 86.43 sec - 480,081,920 bytes |
