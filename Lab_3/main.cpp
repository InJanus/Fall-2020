//Mrugesh Patel
//Brian Culberson
//Gregory Barker
//Homework 3, Data Structures and Algorithms
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
using namespace std;

class Person{
  public: 
    string last_name;
    string first_name;
    int phone;
    Person(){  //constructor
      last_name = "Z";
      first_name = "A";
      phone = 1111111111;
    }
};

struct node{
  Person person;
  node*right = nullptr;
  node*left = nullptr;
};

class Book{
  private:
    node* root;
    int size;
  public:
    Book(){//constructor
      size=0;
      root = nullptr;
    } 
    ~Book(){
      cout<<"no destructor statment implemented" << endl;
    }; //Destructor FIXME
    node* getRoot(){
      return root;
    }
    //Adding an entire node basically
    void Add(node* mynode,string first, string last,int number){
      node* temp = new node;
      temp->person.first_name=first;
      temp->person.last_name=last;
      temp->person.phone=number;
      temp->left=nullptr;
      temp->right=nullptr;
      if(root == nullptr){
        root = temp;
      }
      else{
        if(last.compare(mynode->person.last_name)<0)
        {
          if(mynode->left==nullptr)
          {
            mynode->left=temp;
          }
          else{
            //Destroy Temp here? Because memory Leak
            Add(mynode->left,first,last,number);
          }
        }
        else if(last.compare(mynode->person.last_name)>0)
        {
          if(mynode->right ==nullptr)
          {
            mynode->right = temp;
          }
          else{
            //Destroy Temp here? Because memory Leak
            Add(mynode->right,first,last,number);
          }
        }
        else{
          //FIXME handle the same last name case here
        }
      }
      

    }

    void Add(node* mynode, Person tempperson){
      //copy of add above but with person instead of each indivitual item 
      node* temp = new node;
      string first = tempperson.first_name;
      string last = tempperson.last_name;
      int number = tempperson.phone;
      temp->person=tempperson;
      temp->left=nullptr;
      temp->right=nullptr;
      if(root==nullptr){
        root = temp;
      }
      else{
        if(last.compare(mynode->person.last_name)<0)
        {
          if(mynode->left==nullptr)
          {
            mynode->left=temp;
          }
          else{
            //Destroy Temp here? Because memory Leak
            Add(mynode->left,first,last,number);
          }
        }
        else if(last.compare(mynode->person.last_name)>0)
        {
          if(mynode->right ==nullptr)
          {
            mynode->right = temp;
          }
          else{
            //Destroy Temp here? Because memory Leak
            Add(mynode->right,first,last,number);
          }
        }
        else{
          //FIXME handle the same last name case here
        }
      }
      

    }
    // Given a binary search tree, return the node with minimum 
    // value found in that tree. This will be used in delete with two children
    node* minNode(node* node) { 
        struct node* current = node; 
      
        // loop down to find the leftmost leaf 
        while (current && current->left != NULL) 
            current = current->left; 
      
        return current; 
    } 

    //Delete the node but to check if it works return the new root
    node* Delete(node* root, string last ,string first){ 
    // bootstrap case 
    if (root == NULL){
      return root;
    } 
  
    // Last name less than 
    if (last < root->person.last_name){
      root->left = Delete(root->left, last, first); 
    }
  
    // Last name greater than
    else if (last > root->person.last_name){
      root->right = Delete(root->right, last, first); 
    }
  
    // last name is the same as root's last name, then check first
    else{ 
      //First Name less
      if (first < root->person.first_name){
        root->left = Delete(root->left, last, first); 
      }
  
      // First Name greater
      else if (first > root->person.first_name){
        root->right = Delete(root->right, last, first); 
      }
  
        // if last name is the same as root's last name, then delete this node 
        else{ 
            // node with only one child or no child 
            if (root->left == NULL){ 
                struct node *temp = root->right; 
                free(root); 
                return temp; 
            } 
            else if (root->right == NULL) { 
                struct node *temp = root->left; 
                free(root); 
                return temp; 
            } 
      
            // node with two children: Get the inorder successor 
            struct node* temp = minNode(root->right); 
      
            // Copy the inorder successor's content to this node 
            root->person.last_name = temp->person.last_name; 
            root->person.first_name = temp->person.first_name; 
            root->person.phone = temp->person.phone; 

            // Delete the inorder successor 
            root->right = Delete(root->right, temp->person.last_name, temp->person.first_name); 
        } 
    }
    return root; 
} 
    //returns the number of the person
    int Find(node* root, string first, string last){
      node* found = Search(getRoot(),first, last);
      if(found == nullptr)
      {
        //FIXME some sort of error messaging  //error propogation
        //return here
      }
      return found->person.phone;
    }
    node* Search(node* root, string first, string last)
    {
      if(root == nullptr)
      {
        return nullptr;
      }
      else
      {
        if(last.compare(root->person.last_name)== 0 && first.compare(root->person.first_name)==0)
        {
          return root;
        }
        else if (last.compare(root->person.last_name)<0)
        {
          return Search(root->left,first,last);
        }
        else if (last.compare(root->person.last_name)>0)
        {
          return Search(root->right,first,last);
        }
        else if (first.compare(root->person.first_name)<0)
        {
          return Search(root->left,first,last);
        }
        else if (first.compare(root->person.first_name)>0)
        {
          return Search(root->right,first,last);
        }
      }
      return nullptr;
    }


    void Change(string first, string last, int new_number){
      //prolly use Search to make this easier
      node* found = Search(getRoot(),first,last);
      if(found == nullptr)
      {
        //FIXME some sort of error messaging  //error propogation
        //return here
      }
      found->person.phone = new_number;
    }
    //dump the whole list in alphabetical order 
    void Display(node* mynode){
      //using Inorder traversal
      if(mynode != nullptr)
      {
        Display(mynode->left);
        cout << "LastName: "+mynode->person.last_name +"    FirstName: "+ mynode->person.first_name + "    Number: "<< mynode->person.phone <<endl;
        Display(mynode->right);
      }
    }
    void Quit(node* root, ofstream& outfile){
      //Dump the list into a text file
      if (root != nullptr){
        outfile << root->person.last_name +","+ root->person.first_name+ ","<< root->person.phone << endl;
        Quit(root->left, outfile);
        Quit(root->right, outfile);
      }
    }
    //User Interface 
};

class Gui{
  public:
    Gui(Book book){
      Person myperson;
      int number = 0; 
      
      //Choices the Users have
      cout << "Lab 3" << endl;
      cout << "1 - add user" << endl;
      cout << "2 - delete person" << endl;
      cout << "3 - find person" << endl;
      cout << "4 - change person" << endl;
      cout << "5 - display book" << endl;
      cout << "6 - quit" << endl;

      while(number != 6){
          cin.clear();
          fflush(stdin);
          cout << "Input: ";
          cin >> number;
          switch(number){
              //Insert
              case(1):
                cin.clear();
                fflush(stdin); //flush input
                cout << endl << "fname: ";
                getline(cin, myperson.first_name);
                cout << endl << "lname: ";
                getline(cin, myperson.last_name);
                cout << endl << "pnumber: ";
                cin.clear();
                fflush(stdin);
                cin >> myperson.phone;
                cout << myperson.phone;
                book.Add(book.getRoot(),myperson);
                cout << "Added person" << endl;
                break;
              //DELETE
              case(2):
                cin.clear();
                fflush(stdin);
                cout << endl << "fname: ";
                getline(cin, myperson.first_name);
                cout << endl << "lname: ";
                getline(cin, myperson.last_name);
                book.Delete(book.getRoot() , myperson.last_name, myperson.first_name);
                break;
              //FIND
              case(3):
                cin.clear();
                fflush(stdin);
                cout << endl << "fname: ";
                getline(cin, myperson.first_name);
                cout << endl << "lname: ";
                getline(cin, myperson.last_name);
                cout << "Phone number of found person: " << book.Find(book.getRoot(), myperson.first_name, myperson.last_name) << endl;
                break;
              //CHANGE
              case(4):
                cin.clear();
                fflush(stdin);
                cout << endl << "fname: ";
                getline(cin, myperson.first_name);
                cout << endl << "lname: ";
                getline(cin, myperson.last_name);
                cout << endl << "pnumber: ";
                cin.clear();
                fflush(stdin);
                cin >> myperson.phone;
                book.Change(myperson.first_name, myperson.last_name, myperson.phone);
                break;
              //DISPLAY
              case(5):
                cout << "Displaying PhoneBook" << endl;
                book.Display(book.getRoot());
                break;
              //QUIT
              case(6):
                cout << "exiting..." << endl;
                break;
              default:
                  cout << "invalid selection!" << endl;
                  break;
              }
          }
        }
    };

int main(){
  ofstream outfile;
  outfile.open("PhoneBook.txt");
  Book book;
  Gui newgui(book);
  //STILL TESTING
  //node * rootinMain = book.getRoot();
  outfile.close();
  return 0;
}