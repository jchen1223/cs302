// volsort.h

#ifndef VOLSORT_H
#define VOLSORT_H

#include <cstdlib>
#include <iostream>
#include <string>

struct Node {
  std::string string;
  int number;
  Node *next;
};

struct List {
  Node *head;
  size_t size;

  List();  // define in list.cpp
  ~List(); // define in list.cpp

  void push_front(const std::string &s) {
    if (head == NULL) {
      Node *newNode = new Node();
      newNode->string = s;
      size += 1;

      int num = std::stoi(s);
      newNode->number = num;
      head = newNode;
      newNode->next = NULL;
    } else {
      // create the node and fill in the fields
      Node *newNode = new Node();
      int num = std::stoi(s);
      newNode->number = num;
      newNode->string = s;
      size += 1;

      // set the links
      newNode->next = head;
      head = newNode;
    }
  }; // define below
};

// Functions -------------------------------------------------------------------

bool node_number_compare(
    const Node *a,
    const Node *b); // implement in list.cpp to avoid compile-time issues, used
// by quick, merge and stl
bool node_string_compare(const Node *a,
                         const Node *b); // implement in list.cpp to avoid

// compile-time issues, merge and stl

// Zach Lecture:
// Purpose of a .h file; function declaration
// this is fine
// void woo();
// void woo();
// can declare a function a thousand times in a file, no issues.

// this is not okay
// void woo() {}
// void woo() {}

// #include ".h"
// this is full text replacement
// goes to the file and adds it.

// there is a way around this issue.
// you can have the function declaration in the class.

void dump_node(Node *n); // implement in this file (volsort.h) to make it easier
// for TAs to grade

void stl_sort(List &l,
              bool numeric); // define in stl.cpp - sort using std::sort
void qsort_sort(
    List &l,
    bool numeric); // define in qsort.cpp - sort using qsort from cstdlib
void merge_sort(List &l,
                bool numeric); // define in merge.cpp - your implementation
void quick_sort(List &l,
                bool numeric); // define in quick.cpp - your implementation

#endif
