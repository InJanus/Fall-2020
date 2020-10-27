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
    // if(current == head && head == nullptr)
    // {
    //   node* head = new node;
    //   head->data = input;
    //   head->next = nullptr;
    //   current = head;
    //   return head;
    // }
    if (current == nullptr) {
      //
      node *temp = new node();
      temp->data = input;
      temp->next = nullptr;
      current = temp;
      return current;

    } else {
      current->next = Add(current->next, input);
    }
    return current;
  }
  void append(node* current,string input)
  {
    node *temp = new node();
    temp->data=input;
    temp->next = nullptr;
    
    node *last = current;
    if(current==nullptr)
    {
      current=temp;
      return;
    }
    while(last->next != nullptr)
    {
      last=last->next;
    }
    last->next=temp;
    return;
  }


  void Delete(node* current, string searchVal) {
    // FIXME
  }

  void Print(node* current) {

    if (current == nullptr) {
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
  //test Add for LL FIXME
  LL testlist;
  node *root = testlist.getRoot();
  testlist.Add(testlist.getRoot(),"4");
  testlist.Add(testlist.getRoot(),"7");
  testlist.Add(testlist.getRoot(),"5");
  testlist.Print(testlist.getRoot());
  return 0; 
  }