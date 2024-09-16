// merge.cpp

#include "volsort.h"

#include <iostream>
#include <vector>
// Prototypes

Node *msort(Node *head, bool numeric);
void split(Node *head, Node *&left, Node *&right);
Node *merge(Node *left, Node *right, bool numeric);

// Implementations

void merge_sort(List &l, bool numeric) {
  // merge_sort takes a struct List and whether or not the comparison should be
  // numeric and performs the top-down merge sort algorithm. This function
  // serves as a wrapper or helper function for the recursive msort function.

  // Important to set the l.head to the newly sorted linked list.
  // Without it, it returns the sorted right side of the linked list from msort.
  l.head = msort(l.head, numeric);
}

Node *msort(Node *head, bool numeric) {
  // msort is the recursive portion of the algorithm and calls split to divide
  // and calls merge to conquer. It returns the new head of the list.

  // Handle base cases
  if (head == NULL || head->next == NULL) {
    // There is only one node or no node therefore size of 1 or 0.
    return head;
  }

  // Divide into left and right sublists
  Node *left;
  Node *right;
  split(head, left, right);

  // Recursion
  // Conquer left and right sublists
  left = msort(left, numeric);
  right = msort(right, numeric);

  // Combine left and right sublists
  Node *sorted = merge(left, right, numeric);
  return sorted;
}

void split(Node *head, Node *&left, Node *&right) {
  // Split is a helper function that splits the singly-linked list in half
  // by using the slow and faster pointer trick (aka [tortoise and hare])
  if (head == nullptr) {
    left = nullptr;
    right = nullptr;
    return;
  }

  Node *fast = head;
  Node *slow = head;
  Node *lag = NULL;

  // fast->next != NULL is for odd number of nodes in the linked list
  // fast != NULL is for even number of nodes in the linked list
  while (fast != NULL && fast->next != NULL) {
    lag = slow;
    fast = fast->next->next;
    slow = slow->next;
  }

  // Slow would be the mid point and thus will be the beginning of our right
  // side linked list. Having a lag pointer will allow us to make the end of the
  // left side linked list. Left is always just the head pointer.
  right = slow;
  lag->next = NULL;
  left = head;
}

Node *merge(Node *left, Node *right, bool numeric) {
  // merge is a helper function that combines both the left and right lists and
  // returns the new head of the list.

  // The idea is inspired by Dr. Emrich's notes
  // We create a dummy node that will hold the newly sorted linked list.
  // Then we have a tail set to the dummy node, and we compare the left and
  // right linked list. Whichever is smaller we add on to our tail and increment
  // the tail and whichever linked list that was smaller. We return dummy.next
  // which will be the newly sorted linked list.
  Node dummy;
  Node *tail = &dummy;
  dummy.next = NULL;

  while (left != NULL && right != NULL) {
    // Integer merge comparison
    if (numeric == true) {
      if (left->number < right->number) {
        tail->next = left;
        left = left->next;
      } else {
        tail->next = right;
        right = right->next;
      }
    } else {
      // String merge comparison
      if (left->string < right->string) {
        tail->next = left;
        left = left->next;
      } else {
        tail->next = right;
        right = right->next;
      }
    }
    tail = tail->next;
  }

  // The other linked list is exhausted. Then we just add on the other linked
  // list we are comparing it to.
  while (right != NULL) {
    tail->next = right;
    right = right->next;
    tail = tail->next;
  }
  while (left != NULL) {
    tail->next = left;
    left = left->next;
    tail = tail->next;
  }

  // Set the head pointer to the newly sorted linked list and finally return
  return dummy.next;
}
