// qsort.cpp

#include "volsort.h"

#include <array>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <string.h>

// Inspired by Dr. Emrich's notes.

// Will need two comparative functions both returning ints.
// i.e. Returns a int while comparing ints and strings
int compareIntNodes(const void *a, const void *b) {
  // Cast pointer types
  // A void* pointer is a pointer that can point to any data type.
  // It is a way to store a pointer to some memory without specifying what type
  // of data is stored there.

  // Const void* means that the pointer itself can be changed to point somewhere
  // else, but the data it points to cannot be modified through this pointer.
  // This means that we need to cast void* because it is a generic pointer and
  // does not carry type information.

  // The comparison function receives pointers to the elements being compared,
  // not the elements themselves. This means that the function receives the
  // addresses of the elements in the array. You need to cast void* to Node**
  // because you are dealing with pointers to Node*, not direct Node*.
  // *(Node **)a dereferences the Node ** to be Node *
  // Then we can set it to a variable.

  // In summary, the comparison function, qsort, deals with pointers.
  // Thus we don't want the pointer to the node itself but want the pointer to
  // the pointer to the node. Why do we not want the pointer to the node itself?
  // Because our array is filled with the pointer to the node itself.
  // Thus we have to make it into another pointer that points to the pointer
  // that points to the node. This is all because qsort wants the pointer of
  // what we are dealing with.

  // Zach Lecture:
  // A comparison function is needed for comparing things when there are
  // things that you want to compare that doesn't have a built in comparator.
  // void* is really a double pointer. It really grabs a pointer to the node*
  // pointer that is passed through

  Node *aNode = *(Node **)a;
  Node *bNode = *(Node **)b;

  if (aNode->number < bNode->number)
    return -1;
  else if (aNode->number > bNode->number)
    return 1;
  else
    return 0;
}

int compareStrNodes(const void *a, const void *b) {
  Node *aNode = *(Node **)a;
  Node *bNode = *(Node **)b;

  // Converts them to c-style strings.
  const char *aString = aNode->string.c_str();
  const char *bString = bNode->string.c_str();

  return strcmp(aString, bString);
}

void qsort_sort(List &l, bool numeric) {
  // Same idea as stl.cpp, however, we use an array.
  Node *arr[l.size];
  Node *curr = l.head;

  for (size_t i = 0; i < l.size; i++) {
    arr[i] = curr;
    curr = curr->next;
  }

  if (numeric == true) {
    std::qsort(arr, l.size, sizeof(Node *), compareIntNodes);
  } else {
    std::qsort(arr, l.size, sizeof(Node *), compareStrNodes);
  }

  // Same idea from stl.cpp
  // Set all the links via array.
  for (size_t i = 0; i < l.size - 1; i++) {
    arr[i]->next = arr[i + 1];
  }
  // Set the last node to point to NULL.
  arr[l.size - 1]->next = NULL;

  // Move the head pointer to the newly sorted linked list.
  l.head = arr[0];
}
