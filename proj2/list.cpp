#include "volsort.h"

List::List() { head = nullptr; }

List::~List() {
  Node *ptr = head;
  while (ptr != NULL) {
    Node *next = ptr->next; // saves next pointer
    delete ptr;             // delete current pointer
    ptr = next;             // move to next pointer
  }

  // the reason why you can't do ptr = ptr-> next is because you the current
  // node that the ptr pointer points to. since you deleted it, you cannot
  // access the next node.
}
