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

bool node_number_compare(const Node *a, const Node *b) {
  int aNum = a->number;
  int bNum = b->number;

  // allows for it to be sorted in ascending order.
  if (aNum < bNum) {
    return true;
  } else {
    return false;
  }
}

bool node_string_compare(const Node *a, const Node *b) {
  std::string aNum = a->string;
  std::string bNum = b->string;
  if (aNum < bNum) {
    return true;
  } else {
    return false;
  }
}

// Prints out the node passed in and the other nodes connected and onwards
void dump_node(Node *n) {
  while (n->next != NULL) {
    std::cout << n->number << std::endl;
    std::cout << n->next << std::endl;
    n->next = n;
  }
}
