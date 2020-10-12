//Mrugesh Patel
//Brian Culberson
//Gregory Barker
//Homework 3, Data Structures and Algorithms
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
using namespace std;


class Person{
  public: 
    string last_name;
    string first_name;
    double phone;
    //[FIXME] Need a constructor here
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
    //~Book(); //Destructor FIXME
    node* getRoot(){
      return root;
    }
    //Adding an entire node basically
    void Add(node* mynode,string first, string last,double number){
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

    void Add(node* root, Person tempperson){
      //copy of add above but with person instead of each indivitual item 
      node* temp = new node;
      string first = tempperson.first_name;
      string last = tempperson.last_name;
      double number = tempperson.phone;
      temp->person.first_name=first;
      temp->person.last_name=last;
      temp->person.phone=number;
      temp->left=nullptr;
      temp->right=nullptr;
      if(root==nullptr){
        root = temp;
      }
      else{
        if(last.compare(root->person.last_name)<0)
        {
          if(root->left==nullptr)
          {
            root->left=temp;
          }
          else{
            //Destroy Temp here? Because memory Leak
            Add(root->left,first,last,number);
          }
        }
        else if(last.compare(root->person.last_name)>0)
        {
          if(root->right ==nullptr)
          {
            root->right = temp;
          }
          else{
            //Destroy Temp here? Because memory Leak
            Add(root->right,first,last,number);
          }
        }
        else{
          //FIXME handle the same last name case here
        }
      }
      

    }
        // Given a binary search tree, return the node with minimum 
    // value found in that tree. This will be used in delete with two children
    struct node * minNode(struct node* node) 
    { 
        struct node* current = node; 
      
        // loop down to find the leftmost leaf 
        while (current && current->left != NULL) 
            current = current->left; 
      
        return current; 
    } 

    //Delete the node but to check if it works return the new root
    struct node* deleteNode(struct node* root, string last ,string first){ 
    // bootstrap case 
    if (root == NULL){
      return root;
    } 
  
    // Last name less than 
    if (last < root->person.last_name){
      root->left = deleteNode(root->left, last, first); 
    }
  
    // Last name greater than
    else if (last > root->person.last_name){
      root->right = deleteNode(root->right, last, first); 
    }
  
    // last name is the same as root's last name, then check first
    else{ 
      //First Name less
      if (first < root->person.first_name){
        root->left = deleteNode(root->left, last, first); 
      }
  
      // First Name greater
      else if (first > root->person.first_name){
        root->right = deleteNode(root->right, last, first); 
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
            root->right = deleteNode(root->right, temp->person.last_name, temp->person.first_name); 
        } 
    }
    return root; 
} 
    //returns the number of the person
    double Find(node* root, string first, string last){
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
    }


    void Change(string first, string last, double new_number){
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
    void Display(node* root){
      //using Inorder traversal
      if(root != nullptr)
      {
        Display(root->left);
        cout << "LastName: "+root->person.last_name +"    FirstName: "+ root->person.first_name+ "    Number: "<<root->person.phone<<endl;
        Display(root->right);
      }
    }
    void Quit(node* root){
      //Dump the list using Preorder
      if (root != nullptr)
      {
        //Dump The list into dummy file
        //FIXME
        Quit(root->left);
        Quit(root->right);
      }
    }
};









int main()
{
  Book book;
  //STILL TESTING
  //node * rootinMain = book.getRoot();
  Person myperson;
  book.Add(book.getRoot(),"Igum","Patel",5131234569);
  book.Add(book.getRoot(),"Greg","Barker",5131234567);
  book.Add(book.getRoot(),"Brendo","Parker",5130123456);
  book.Add(book.getRoot(),"Minglio","Zarkyr",5130123455);
  book.Display(book.getRoot());

  int number = 0;
        
        
  cout << "Lab 3" << endl;
  cout << "1 - add user" << endl;
  cout << "2 - delete person" << endl;
  cout << "3 - find person" << endl;
  cout << "4 - change person" << endl;
  cout << "5 - display book" << endl;
  cout << "6 - quit" << endl;

  
  while(number != 6){
      cin >> number;

      
      switch(number){
          case(1):
            cout << "fname: ";
            getline(cin, myperson.first_name);
            cout << endl << "lname: ";
            getline(cin, myperson.last_name);
            cout << endl << "pnumber: ";
            cin >> myperson.phone;
            book.Add(book.getRoot(),myperson);
            break;
          case(2):
            cout << "fname: ";
            getline(cin, myperson.first_name);
            cout << endl << "lname: ";
            getline(cin, myperson.last_name);
            book.Delete(myperson.first_name, myperson.last_name);
            break;
          case(3):
            break;
          case(4):
            break;
          case(5):
            break;
          case(6):
            cout << "exiting..." << endl;
            break;
          default:
              cout << "invalid selection!" << endl;
              break;
          }
      }

  return 0;
}