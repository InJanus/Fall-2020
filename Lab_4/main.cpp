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

class node {
 public:
  string data;
  node* next;
};

class LL {
 private:
  node* head;

 public:
  // Constructor
  LL() { head = nullptr; }
  node* getRoot() { return head; }
  void Insert(node* current, string input) {
    node* temp = new node();
    temp->data = input;
    temp->next = nullptr;

    node* last = current;
    if (head == nullptr) {
      head = temp;
      return;
    }
    while (last->next != nullptr) {
      last = last->next;
    }
    last->next = temp;
    return;
  }

  void Delete(node* current, string searchVal) {
    node* found = Search(current, searchVal);
    if (found == head) {
      head = head->next;
    }
    free(found);
  }

  void Print(node* current) {
    if (current == nullptr) {
      return;
    }
    cout << current->data << " ";
    Print(current->next);
  }

  node* Search(node* current, string searchVal) {
    if (current == nullptr) {
      return nullptr;
    }
    if (current->data == searchVal) {
      return current;
    }
    return Search(current->next, searchVal);
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
  // test Add for LL FIXME
  LL testlist;
  node* root = testlist.getRoot();
  testlist.Insert(testlist.getRoot(), "4");
  testlist.Insert(testlist.getRoot(), "7");
  testlist.Insert(testlist.getRoot(), "5");
  testlist.Print(testlist.getRoot());
  cout << endl;
  testlist.Delete(testlist.getRoot(), "4");
  testlist.Print(testlist.getRoot());
  return 0;
}