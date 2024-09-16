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
  msort(l.head, numeric);
}

Node *msort(Node *head, bool numeric) {
  // msort is the recursive portion of the algorithm and calls split to divide
  // and calls merge to conquer. It returns the new head of the list.

  // Handle base cases
  if (head == NULL || head->next == NULL) {
    // There is only one node or no node therefore size of 1 or 0.
    return head;
  }

  if (head->next->next == NULL) {
    // There is two nodes therefore you compare and possibly swap.

    Node *first = head;
    Node *second = head->next;

    // If it is a integer comparison
    if (numeric == true) {
      if (first->number < second->number) {
        return head;
      } else {
        // If the second node is less than the first node, relink for the second
        // node to be the first. Sets the second node to point to the first
        // node.
        second->next = first;
        // Sets the first node to point to the end.
        first->next = NULL;
        // Sets the head pointer to be the second node making the second node
        // the new first node, or in this case return second aka new head node.
        return second;
      }
    }

    // Else, it is a string comparison
    else {
      if (first->string < second->string) {
        return head;
      } else {
        second->next = first;
        first->next = NULL;
        return second;
      }
    }
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
  /* TODO */
  // (Check this, may or may not be wrong.)
  return merge(left, right, numeric);
}

void split(Node *head, Node *&left, Node *&right) {
  // Split is a helper function that splits the singly-linked list in half
  // by using the slow and faster pointer trick (aka [tortoise and hare])
  Node *fast = head;
  Node *slow = head;

  // fast->next != NULL is for odd number of nodes in the linked list
  // fast != NULL is for even number of nodes in the linked list
  while (fast != NULL && fast->next != NULL) {
    fast = fast->next->next;
    slow = slow->next;
  }

  // The reason why we do not need fast->next = NULL is because
  // given an odd number of nodes in a linked list,
  // fast->next = NULL and fast->next->next would be dangerous.
  right = slow->next;
  slow->next = NULL;
  left = head;
}

Node *merge(Node *left, Node *right, bool numeric) {
  // merge is a helper function that combines both the left and right lists and
  // returns the new head of the list.

  // Create a vector to hold the sorted linked list.
  std::vector<Node *> tempVector;
  // Create a new Node* head, this will be what will be returned.
  Node *head;

  // Integer comparison merge
  while (left->next != NULL && right->next != NULL) {
    if (numeric == true) {
      // Compare both nodes, whichever one is less than the other will be pushed
      // back Whichever linked that was pushed to the vector will move to its
      // next node.
      if (left->number < right->number) {
        tempVector.push_back(left);
        left = left->next;
      } else {
        tempVector.push_back(right);
        right = right->next;
      }
    }

    // String comparison merge
    else {
      if (left->number < right->number) {
        tempVector.push_back(left);
        left = left->next;
      } else {
        tempVector.push_back(right);
        right = right->next;
      }
    }
  }

  // The other linked list has its end. Then we just add on the other linked
  // list we are comparing it to.
  if (right->next == NULL) {
    tempVector.push_back(left);
    left = left->next;
  }

  // Now do the same but this time the left linked list needs to be added on.
  if (left->next == NULL) {
    tempVector.push_back(right);
    right = right->next;
  }

  /* TODO */
  // Think about when one of the linked list hits the end.
  // It would mean we would have to push the other linked list onto the vector
  // (if sorted).

  /* TODO */
  // Perhaps make left and right pointers sorted already before adding them in?

  // Need to add the implementation of correctly linking everything together
  for (size_t i = 0; i < tempVector.size() - 1; i++) {
    tempVector[i]->next = tempVector[i + 1];
  }

  // Set the last node to point to null.
  tempVector[tempVector.size() - 1]->next = NULL;

  // Set the head pointer to the newly sorted linked list and finally return
  head = tempVector[0];
  return head;
}
