// stl.cpp

#include "volsort.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void stl_sort(List &l, bool numeric) {
  // Create a vector that will hold all the pointers to each of the indiviudal
  // nodes in the list.
  vector<Node *> vec;

  // Fill the vector with all the node *;
  // Node* curr is outside because if it was in the for loop it would always set
  // it to beginning. Node* curr is an independent pointer of head pointer, so
  // updating it does not change head pointer. Node* curr access head pointer
  // because current is set to point to the same node as head.
  Node *curr = l.head;
  while (curr != NULL) {
    vec.push_back(curr);
    curr = curr->next;
  }

  // Now we want to call sort on the vector

  // Function pointers, sort need a way to compare so we pass in the function
  // pointer to compare. When you use the function name without (), you're
  // passing a pointer to the function.
  if (numeric == true) {
    sort(vec.begin(), vec.end(), node_number_compare);
  } else {
    sort(vec.begin(), vec.end(), node_string_compare);
  }

  // Now we want to relink the nodes in the list
  // This will relink every node beside the one the head pointer is pointing to.
  for (size_t i = 0; i < l.size - 1; i++) {
    // We want to save the old list so we can properly relink each node, so we
    // save it on a tempNode before updating the old list.
    vec[i]->next = vec[i + 1];
  }
  // This will fix the last node to point to NULL
  vec[l.size - 1]->next = NULL;

  // Move the head pointer to the newly sorted list made from the vector. This
  // way it will print out the newly sorted linked list.
  l.head = vec[0];
}
