// quick.cpp

#include "volsort.h"
#include <iostream>
#include <cstring>
using namespace std;

// Prototypes
Node *qsort(Node *head, bool numeric);
void  partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric);
Node *concatenate(Node *left, Node *right);

// Implementations
void quick_sort(List &l, bool numeric) {
    l.head = qsort(l.head, numeric);
}

Node *qsort(Node *head, bool numeric) {
    
    if (!head || !head->next) {
        return head;
    }

    Node *left = nullptr, *right = nullptr;

    partition(head->next, head, left, right, numeric);

    left = qsort(left, numeric);
    right = qsort(right, numeric);

    head->next = right;

    return concatenate(left, head);
}

void partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric) {
    
    Node *leftTail = nullptr, *rightTail = nullptr;

    while (head) {
        Node *next = head->next;
        head->next = nullptr;

        bool compareResult;
        
        if (numeric) {
            compareResult = stoi(head->value) < stoi(pivot->value);
        } else {
            compareResult = head->value < pivot->value;
        }

        if (compareResult) {
            if (!left) {
                left = leftTail = head;
            } else {
                leftTail->next = head;
                leftTail = head;
            }
        } else {
            if (!right) {
                right = rightTail = head;
            } else {
                rightTail->next = head;
                rightTail = head;
            }
        }

        head = next;
    }
}

Node *concatenate(Node *left, Node *right) {
    
    if (!left) return right;

    Node *current = left;
    
    while (current->next) {
        current = current->next;
    }
    
    current->next = right;
    
    return left;
}

// Main function for testing and command-line interface
int main(int argc, char *argv[]) {
    
    bool numeric = false;
    string mode = "quick";

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        
        if (strcmp(argv[i], "-n") == 0) {
            numeric = true;
        } else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            mode = argv[++i];
        } else if (strcmp(argv[i], "-h") == 0) {
            cout << "usage: volsort\n"
                 << "    -m MODE   Sorting mode (oblivious, stl, qsort, merge, quick)\n"
                 << "    -n        Perform numerical ordering\n";
            return 0;
        }
    }

    // Read input and create list
    List list;
    string value;
    
    while (cin >> value) {
        
        Node *newNode = new Node{value, nullptr};
        
        if (!list.head) {
            list.head = newNode;
        } else {
            Node *current = list.head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }


    if (mode == "quick") {
        quick_sort(list, numeric);
    }

    Node *current = list.head;
    
    while (current) {
        cout << current->value << endl;
        current = current->next;
    }

    // Clean up memory
    while (list.head) {
        Node *temp = list.head;
        list.head = list.head->next;
        delete temp;
    }

    return 0;
}
