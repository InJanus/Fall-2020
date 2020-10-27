// Mrugesh Patel
// Brian Culberson
// Gregory Barker
// Homework 4, Data Structures and Algorithms
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct node {
  string data;
  node* next = nullptr;
};

class LL {
 private:
  node* head;

 public:
  // Constructor
  LL() { head = nullptr; }
  node* getRoot() { return head; }
  node* Add(node* current, string input) {
    if (current == nullptr) {
      //
      node* temp = new node;
      temp->data = input;
      // prolly early return or something FIXME
    } else {
      current->next = Add(current->next, input);
      return current;
    }
  }
  void Delete(node* current, string searchVal) {
    // FIXME
  }

  void Print(node* current) {
    if (current == NULL) {
      return;
    }
    cout << current->data << " ";
    Print(head->next);
  }

  node* Search(node* current, string searchVal) {
    if (current == nullptr) {
      return nullptr;
    }
    if (current->data == searchVal) {
      return current;
    }
    return Search(current->next, searchVal)
  }
};

class DiGraph {
 private:
 public:
  // Constructor
  // Destructor
  // Edge addition
  // Edge deletion
};

int main() { 
  //test Add for LL
  return 0; 
  }