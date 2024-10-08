Jeffrey Chen, Aidan Feyerherm, Joey DiSalvo, Cristian Frutos
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
| QSort 10000000 | 73.31 sec - 640,081,920 bytes |
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

1)
- Stl time complexity: O(n log n)
- Qsort time complexity: O(n log n)
- Merge sort time complexity: O(n log n)
- Quick sort time complexity: O(n log n)

STL and qsort are two almost identical sorting algorithms that both run in O(n log n) time. STL sort still tends to be faster due to overhead of the function pointer and how it takes the strong points of other sorting algorithms. Merge sort is generally slower than the previous sorting methods but is consistent in O(n log n). It makes sense for merge sort and quick sort to both require the same amount of memory consumption due to both needing to seperate the linked list into smaller linked list. In other words, there is no need to copy the original linked list to another data structure. Meanwhile for sort and qsort, this is not true. I think it is also important to mention that implementation is also very important. Depending on the implementation merge sort could be slower or faster, or quick sort (depending on how you choose the pivot) can be faster or slower.   

2) Theoretical analysis assumes random input, but the real world has patterns that might be difficult for quick sort, which struggles with already-sorted or nearly-sorted arrays. However, it can be faster in real applications compared to merge sort due to less operations and better cache utilization. STL sort also has a few optimizations that can impact real-world performance. In other words, theoretical complexities provide a high-level understanding of how an algorithm will scale with input size. However, they do not account for constant factors or lower-order terms that can significantly affect real-world performance.

3) Based on the benchmarks, merge sort seemed to be the best choice of sorting. Merge sort seemed to complete its task at a relatively similar time to the rest of “faster” methods. As the data size increased its time stayed steady and its memory usage wasn't as high as other methods for the most part. The other top contender choice is sort as it is the fastest, however, it also demands the most amount of memory since it requires for the linked list to be copied into another data structure, which in this case is a vector.
