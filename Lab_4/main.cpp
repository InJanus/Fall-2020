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
  bool llvisited[SIZE];
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

  
  
  LL DFS(DiGraph graph, string v, LL visited){
    //Mark the start node (v) as found
    //we need to find the starting node in the list of LL

    for(int i = 0; i < actualSize; i++){
      if(graph.heads->getRoot()->data.compare(v)){
        //finds the head of the list that matches the v term
        //if this is true then visited should be ture acording to the paralell array
        llvisited[i] = true;
      }else{
        //FIXME - not sure if i should set this to false by default or set this in thge constructor 
        continue;
      }
    }
    //actual size is needed for n inplementation  
    //is implementation used for setting all variables the same value
    //look at every edge of v
    //thinking about a couter to track what LL we are on
    int counter = 0;
    for(LL neighbors : heads){
      // check if DFS has run on the neighbors
      if(!llvisited[counter]){
        //If DFS not run recursively call function
        DFS(graph, neighbors.getRoot()->data, visited); //not sure if this is correct
      }
      //output v
      return neighbors;
    }
    return LL();
  }
  //topological sorting
  LL topologicalSort(DiGraph graph){
    //int visited[]; imn now thingking that a global variable here will not work since it needs to be recursive
    //create a linked list that will store the DFS results
    LL toplist = LL(); //empty out list and delcare new list

    //go through the entire graph and put
    for(int i = 0; i < actualSize; i++){
      if(!llvisited[i]){
        toplist = DFS(graph, to_string(i), toplist);
      }
    }
    return toplist;
  }

  LL acycliccheck(DiGraph input){
    //checks to see if it is acyclic. means it can be sorted
    //find the drain
    node* testingval = nullptr;
    DiGraph tempgraph = input;
    LL myreturn;
    int mysize;
    string start = heads[0].getRoot()->next->data;
    string remove = "";
    int fixer = 0;
    bool flag = false;
    while(!flag){
      fixer = 0;
      //cout << endl;
      //this->Print();
      remove = getdrain(heads[0].getRoot()->next->data);
      myreturn.Insert(myreturn.getRoot(), remove);
      testingval = nullptr;
      //myreturn.Print(myreturn.getRoot());
      mysize = size(tempgraph);
      for(int i = 0; i < mysize; i++){
        if(tempgraph.heads[i].getRoot() == nullptr){
          fixer = fixer + 1;
        }

        if(tempgraph.heads[i-fixer].getRoot()->next->data == remove && tempgraph.heads[i-fixer].getRoot()->next->next == nullptr){
          for(int n = 0; n < size(tempgraph); n++){
            testingval = tempgraph.heads[n].Search(tempgraph.heads[n].getRoot(), tempgraph.heads[i-fixer].getRoot()->data);
            if(n == (i-fixer)){
              testingval = nullptr;
            }
            if(testingval){
              break;
            }
          }
          
          if(!testingval){
            myreturn.Insert(myreturn.getRoot(), tempgraph.heads[i-fixer].getRoot()->data);
          }
        } 

        tempgraph.delEdge(tempgraph.heads[i-fixer].getRoot()->data, remove); //delete the node from the list
      }
      if(size(tempgraph) == 1){
        myreturn.Insert(myreturn.getRoot(), tempgraph.heads[0].getRoot()->data);
        flag = !flag;
      }
    }
    return myreturn;
  }

  string getdrain(string inputtemp){
    string temp = inputtemp;
    node* tempnode;
    bool flag = false;
    while(!flag){
      for(int i = 0; i < actualSize; i++){
        if(temp == heads[i].getRoot()->data){
          temp = heads[i].getRoot()->next->data;
          break;
        }
        if(i == actualSize-1){
          flag = !flag;
        }
      }
    }
    //comment out for production version
    //cout << temp << endl;
    return temp;
  }
  
  int size(DiGraph input){
    int i = 0;
    while(input.heads[i].getRoot() != nullptr){
      i++;
    }
    return i;
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
  
  // //ui programing
  // LL test3;
  // DiGraph test2;
  // bool flag = false; //exit checker
  // int counter = 0; //starting list counter
  // string temp[SIZE];

  // //to enter the list or do other delete functions add a start menu to the list


  // cout << "Enter \"!\" to exit list enter" << endl;
  // while(!flag){
  //   //enter data untill a stop has been reached
  //   cout << counter << " : ";
  //   getline(cin, temp[counter]); //input temp array for ordering list
    
  //   if(temp[counter] == "!"){ 
  //     temp[counter] = "";
  //     flag = !flag;
  //     counter--;
  //   } //exiting the loop
  //   counter++;
  // }
  // flag = !flag;
  // cout << "Enter list items with spaces inbetween, ie \"1 2\", this means item 1 is the source to item 2" << endl;
  // cout << "Enter -1 -1 to exit" << endl;
  // for(int i = 0; i < counter; i++){
  //   cout << i << " : " << temp[i] << endl;
  // }
  // int optone, opttwo;
  // while(!flag){
  //   //this loop is for entering the connections
  //   //ex 1 2 would mean 1 is connected to 2
  //   //i am avoiding to type string because this makes it hard to type everyting efficently
  //   //hopefuly if we have time i can add this functionality to change this
  //   cin >> optone >> opttwo; //insert with space inbetween for input
  //   if(optone == -1 && opttwo == -1){ 
  //     flag = !flag; 
  //   }else{ //posibly check for range
  //     cout << "added: " << temp[optone] << " " << temp[opttwo] << endl;
  //     test2.addEdge(temp[optone], temp[opttwo]);
  //   }
  // }
  // test2.Print();
  // cout << "=========================== acycliccheck ===========================" << endl;
  // test3 = test2.acycliccheck(test2);
  // test3.Print(test3.getRoot());
  

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
  LL test2;
  test.addEdge("5","0");
  test.addEdge("5","2");
  test.addEdge("2","3");
  test.addEdge("3","1");
  test.addEdge("4","0");
  test.addEdge("4","1");
  //test.addEdge("3","4");
  
  test.Print();
  test2 = test.acycliccheck(test);
  cout << endl;
  test2.Print(test2.getRoot());
  return 0;
}