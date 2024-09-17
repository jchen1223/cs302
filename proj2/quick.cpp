// quick.cpp

#include "volsort.h"
#include <cstring>
#include <iostream>
using namespace std;

// Prototypes
Node *qsort(Node *head, bool numeric);
void partition(Node *head, Node *pivot, Node *&left, Node *&right,
               bool numeric);
Node *concatenate(Node *left, Node *right);

// Implementations
void quick_sort(List &l, bool numeric) { l.head = qsort(l.head, numeric); }

Node *qsort(Node *head, bool numeric) {
  // Base case
  // When there is an empty node or if there is only one node in the linked
  // list.
  if (head == NULL || head->next == NULL) {
    return head;
  }

  Node *left = nullptr;
  Node *right = nullptr;
  Node *pivot = head;

  partition(head->next, pivot, left, right, numeric);

  // Recursion.
  left = qsort(left, numeric);
  right = qsort(right, numeric);

  // Pivot node needs to be set to nullptr to signify an alone node.
  pivot->next = NULL;

  // Conqueror the list.
  Node *sorted = concatenate(left, pivot);
  sorted = concatenate(sorted, right);

  return sorted;
}

void partition(Node *head, Node *pivot, Node *&left, Node *&right,
               bool numeric) {

  Node *curr = head;
  Node dummyLeft;
  Node dummyRight;

  dummyLeft.next = NULL;
  dummyRight.next = NULL;
  Node *leftptr = &dummyLeft;
  Node *rightptr = &dummyRight;

  while (curr != NULL) {
    if (numeric == true) {
      // Integer comparison
      if (curr->number < pivot->number) {
        // If the current number is less than the pivot number
        // then move to the left side.
        leftptr->next = curr;
        leftptr = leftptr->next;
      } else {
        rightptr->next = curr;
        rightptr = rightptr->next;
      }
    } else {
      // String comparison
      if (curr->string < pivot->string) {
        leftptr->next = curr;
        leftptr = leftptr->next;
      } else {
        rightptr->next = curr;
        rightptr = rightptr->next;
      }
    }
    curr = curr->next;
  }

  // End the two lists.
  leftptr->next = NULL;
  rightptr->next = NULL;

  // Set the results
  left = dummyLeft.next;
  right = dummyRight.next;
}

Node *concatenate(Node *left, Node *right) {
  // The idea is to add the left linked list with the pivot,
  // then add that new linked list to the right linked list.

  // If the left side of our linked list is empty, return the right.
  if (left == NULL) {
    return right;
  }
  // Same for the other side.
  if (right == NULL) {
    return left;
  }

  Node *current = left;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = right;

  return left;
}
