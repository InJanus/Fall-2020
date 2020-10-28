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
const int SIZE = 200;

//establish class node for use
class node {
 public:
  string data;
  node* next;
};

//Linked List was specified in the document
class LL {
 private:
  node* head;
  int size;

 public:
  // Constructor
  LL() {
    head = nullptr;
    size = 0;
  }
  //Get the head of the list
  node* getRoot() { 
    return head; 
  }
  //Get the size of the list
  int getSize() { 
    return size; 
  }
  //Insert a value to the list, in this case a string
  void Insert(node* current, string input) {
    node* temp = new node();
    temp->data = input;
    temp->next = nullptr;

    node* last = current;
    //empty list case
    if (head == nullptr) {
      head = temp;
      size++;
      return;
    }
    //look for the next "open" spot on the list
    while (last->next != nullptr) {
      last = last->next;
    }
    last->next = temp;
    size++;
    return;
  }

  //Delete a node from the array
  void Delete(node* current, string searchVal) {
    node* temp = head;
    node* prev = nullptr;
    if(temp!=nullptr && temp->data == searchVal)
    {
      head = temp->next;
      delete temp;
      return;
    }
    //check if node doesn't exist in list
    while (temp != nullptr && temp->data != searchVal)
    {
      prev = temp;
      temp = temp->next;
    }
    //if node doesn't exist return
    if (temp == nullptr){
      return;
    }
    prev->next = temp->next;
    //actually get rid of temp
    delete temp;
    //decrease size
    size--;
  }

  //Print out the list 
  void Print(node* current) {
    if (current == nullptr) {
      return;
    }
    cout << current->data << " ";
    //recursive to get the whole list
    Print(current->next);
  }

  //Search for a specific node within the list
  node* Search(node* current, string searchVal) {
    if (current == nullptr) {
      return nullptr;
    }
    if (current->data == searchVal) {
      return current;
    }
    //recursive call
    return Search(current->next, searchVal);
  }
  //Delete Linked List 
  void DeleteLL(){
    node* current = head;
    node* next;
    while(current!= nullptr)
    {
      next=current->next;
      //free up memory
      free(current);
      current=next;
    }
    head = nullptr;
    size=0;
  }
};

// Establish the Digraph
class DiGraph {
 private:
  LL heads[SIZE];
  int actualSize;

 public:
  // Constructor
  DiGraph() { actualSize = 0; }
  // Edge addition
  void addEdge(string head, string tail) {
    for (int i = 0; i < actualSize; i++) {
      // If the head exists in the structure
      if (heads[i].getRoot()->data == head) {
        heads[i].Insert(heads[i].getRoot(), tail);
        return;
      }
    }
    //Utilize the linked list class to add in edge
    heads[actualSize].Insert(heads[actualSize].getRoot(), head);
    heads[actualSize].Insert(heads[actualSize].getRoot(), tail);
    actualSize++;
  }

  //Delete Edge
  void delEdge(string head, string tail) {
    for(int i=0; i<actualSize; i++){
      //Finding head in the array of Heads
      if(heads[i].getRoot()->data == head)
      {
        //finding tail in the LL for head
        if (heads[i].Search(heads[i].getRoot(),tail)!=nullptr){
          if (heads[i].getSize()==2)
          {
            //entering here means that the only nodes are head and tail in the LL, thus need to del both
            //Del the list i
            heads[i].DeleteLL();
            heads[i]=heads[actualSize-1];
            heads[actualSize-1]= LL();
            actualSize--;
            return; 
          }
          //general case where you want to get rid of some tail within the head LL
          heads[i].Delete(heads[i].getRoot(),tail);
        }
      }
    }
  }

  //Print the Digraph
  void Print() {
    for (int i = 0; i < actualSize; i++) {
      heads[i].Print(heads[i].getRoot());
      cout << endl;
    }
  }
  // Destructor
};

int main() {
  //******LL TESTING******
  // LL testlist;
  // testlist.Insert(testlist.getRoot(), "4");
  // testlist.Insert(testlist.getRoot(), "7");
  // testlist.Insert(testlist.getRoot(), "5");
  // testlist.DeleteLL();
  // testlist.Print(testlist.getRoot());
  // cout << endl;
  // cout << "SIZE: " << testlist.getSize() << endl;
  // testlist.Delete(testlist.getRoot(), "4");
  // testlist.Print(testlist.getRoot());
  // cout << endl;
  // cout << "SIZE: " << testlist.getSize() << endl;

//******DiGraph TESTING******
  DiGraph test;
  test.addEdge("5", "3");
  test.addEdge("5", "2");
  test.addEdge("5","6");
  test.addEdge("6", "3");
  test.delEdge("6","3");
  test.Print();
  return 0;
}