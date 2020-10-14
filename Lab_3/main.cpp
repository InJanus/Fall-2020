//Mrugesh Patel
//Brian Culberson
//Gregory Barker
//Homework 3, Data Structures and Algorithms
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
using namespace std;

class Person{
  public: 
    string last_name;
    string first_name;
    string phone; //this should be a string because a integer takes a lot of data to store a full phone number
    Person(){  //constructor
      last_name = "Z";
      first_name = "A";
      phone = "1111111111";
    }
    Person(string first,string last, string number)
    { //constructor
      last_name = last;
      first_name = first;
      phone = number;
    }
};

struct node{
  Person person;
  node *right = nullptr;
  node *left = nullptr;
};

class Book{
private:
  node *root;
  int size;

public:
  Book()
  { //constructor
    size = 0;
    root = nullptr;
    //FIXME reading from the file
  }
  ~Book()
  {
    cout << "no destructor statment implemented" << endl;
  }; //Destructor FIXME
  node *getRoot()
  {
    return root;
  }
  //Adding an entire node to the tree structure recursively
  void Add(node *mynode, Person tempperson)
  {
    //copy of add above but with person instead of each indivitual item
    node *temp = new node;
    string first = tempperson.first_name;
    string last = tempperson.last_name;
    string number = tempperson.phone;
    temp->person = tempperson;
    temp->left = nullptr;
    temp->right = nullptr;
    if (root == nullptr)
    {
      root = temp;
    }
    else
    {
      if (last.compare(mynode->person.last_name) < 0)
      {
        if (mynode->left == nullptr)
        {
          mynode->left = temp;
        }
        else
        {
          //Destroy Temp here? Because memory Leak
          delete temp;
          temp = nullptr;
          Add(mynode->left, tempperson);
        }
      }
      else if (last.compare(mynode->person.last_name) > 0)
      {
        if (mynode->right == nullptr)
        {
          mynode->right = temp;
        }
        else
        {
          //Destroy Temp here? Because memory Leak
          delete temp;
          temp = nullptr;
          Add(mynode->right, tempperson);
        }
      }
      else
      {
        //handle the same last name case here
        if (first.compare(mynode->person.first_name) < 0)
        {
          if (mynode->left == nullptr)
          {
            mynode->left = temp;
          }
          else
          {
            //Destroy Temp here? Because memory Leak
            delete temp;
            temp = nullptr;
            Add(mynode->left, tempperson);
          }
        }
        else if (first.compare(mynode->person.first_name) > 0)
        {
          if (mynode->right == nullptr)
          {
            mynode->right = temp;
          }
          else
          {
            //Destroy Temp here? Because memory Leak
            delete temp;
            temp = nullptr;
            Add(mynode->right, tempperson);
          }
        }
      }
    }
  }
  // Given a binary search tree, return the node with minimum
  // value found in that tree. This will be used in delete with two children
  node *minNode(node *node)
  {
    struct node *current = node;

    // loop down to find the leftmost leaf
    while (current && current->left != NULL)
      current = current->left;
    return current;
  }
  //Delete the node but to check if it works return the new root
  node *Delete(node *root, string last, string first)
  {
    // bootstrap case
    if (root == NULL)
    {
      return root;
    }
    // Last name less than
    if (last < root->person.last_name)
    {
      root->left = Delete(root->left, last, first);
    }
    // Last name greater than
    else if (last > root->person.last_name)
    {
      root->right = Delete(root->right, last, first);
    }
    // last name is the same as root's last name, then check first
    else
    {
      //First Name less
      if (first < root->person.first_name)
      {
        root->left = Delete(root->left, last, first);
      }
      // First Name greater
      else if (first > root->person.first_name)
      {
        root->right = Delete(root->right, last, first);
      }
      // if last name is the same as root's last name, then delete this node
      else
      {
        // node with only one child or no child
        if (root->left == NULL)
        {
          struct node *temp = root->right;
          free(root);
          return temp;
        }
        else if (root->right == NULL)
        {
          struct node *temp = root->left;
          free(root);
          return temp;
        }
        // node with two children: Get the inorder successor
        struct node *temp = minNode(root->right);
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
  //returns the number of the person that is being looked for
  string Find(node *root, string first, string last)
  {
    node *found = Search(getRoot(), first, last);
    if (found == nullptr)
    {
      //error messaging  //error propogation
      cout<<"ERROR: NODE NOT FOUND"<<endl;
      return 0;
      //return here
    }
    return found->person.phone;
  }
  //Utility Function for finding nodes based off of first and last name. Used in Find and Change
  node *Search(node *root, string first, string last)
  {
    if (root == nullptr)
    {
      return nullptr;
    }
    else
    {
      if (last.compare(root->person.last_name) == 0 && first.compare(root->person.first_name) == 0)
      {
        return root;
      }
      else if (last.compare(root->person.last_name) < 0)
      {
        return Search(root->left, first, last);
      }
      else if (last.compare(root->person.last_name) > 0)
      {
        return Search(root->right, first, last);
      }
      else if (first.compare(root->person.first_name) < 0)
      {
        return Search(root->left, first, last);
      }
      else if (first.compare(root->person.first_name) > 0)
      {
        return Search(root->right, first, last);
      }
    }
    return nullptr;
  }
  //Changes the number of the node that is found
  void Change(string first, string last, string new_number)
  {
    //prolly use Search to make this easier
    node *found = Search(getRoot(), first, last);
    if (found == nullptr)
    {
      //error messaging  //error propogation
      cout<<"ERROR: NODE NOT FOUND"<<endl;
      return;
      //return here
    }
    found->person.phone = new_number;
  }
  //dump the whole list in alphabetical order in to the command line
  void Display(node *mynode)
  {
    //using Inorder traversal
    if (mynode != nullptr)
    {
      Display(mynode->left);
      cout <<setw(40)<<"LastName: " + mynode->person.last_name; 
      cout <<setw(40)<<"FirstName: " + mynode->person.first_name;
      cout <<"Number: " << mynode->person.phone; 
      cout<< endl;
      Display(mynode->right);
    }
  }
  //Saves to a outfile specified by the Gui. In our use case it should be PhoneBook.txt
  void Quit(node *root, ofstream &outfile)
  {
    //Dump the list into a text file
    if (root != nullptr)
    {
      outfile << root->person.last_name + "," + root->person.first_name + "," << root->person.phone << endl;
      Quit(root->left, outfile);
      Quit(root->right, outfile);
    }
  }
  void Restore(ifstream &infile)
  {
    string line;
    while (getline(infile,line))
    {
      //string last = line.substr(0,line.find(","));
      //string first = line.substr(line.find(","),line.find_last_of(","));
      //string num =line.substr(line.find_last_of(","),line.length());
      //cout << first <<endl;//+ "  "+first


      // string delimiter = ",";
      // size_t pos = 0;
      // std::string token;
      // while ((pos = line.find(delimiter)) != std::string::npos) {
      //   token = line.substr(0, pos);
      //   std::cout << token << std::endl;
      //   line.erase(0, pos + delimiter.length());
      // }
    }
  }
};

class Gui{
  public:
    Gui(Book book, ofstream& outfile){
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
                cout << "fname: ";
                getline (cin, myperson.first_name);
                cout << "lname: ";
                getline (cin, myperson.last_name);
                cout << "pnumber: ";
                getline(cin, myperson.phone);
                book.Add(book.getRoot(),myperson);
                cout << "Added person" << endl;
                //cout << "would you like to input person again? (y/n)";
                break;
              //DELETE
              case(2):
                cin.clear();
                fflush(stdin);
                cout << "fname: ";
                getline(cin, myperson.first_name);
                cout << "lname: ";
                getline(cin, myperson.last_name);
                book.Delete(book.getRoot() , myperson.last_name, myperson.first_name);
                break;
              //FIND
              case(3):
                cin.clear();
                fflush(stdin);
                cout << endl << "fname: ";
                getline(cin, myperson.first_name);
                cout << "lname: ";
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
                getline(cin, myperson.phone);
                book.Change(myperson.first_name, myperson.last_name, myperson.phone);
                break;
              //DISPLAY
              case(5):
                cout << "Displaying PhoneBook" << endl;
                book.Display(book.getRoot());
                break;
              //QUIT
              case(6):
                book.Quit(book.getRoot(), outfile);
                cout << "exiting..." << endl;
                break;
              default:
                cout << "invalid selection!" << endl;
                break;
              }
          }
        }
    };

int main()
{
  Book book;
  ofstream outfile;
  outfile.open("PhoneBook.txt");
  // Gui newgui(book, outfile);
  // outfile.close();

  // TEST Cases Code
  book.Add(book.getRoot(),Person("Greg","Barker","1234567891"));
  book.Add(book.getRoot(),Person("Mugs","Patel","1134567891"));
  book.Add(book.getRoot(),Person("Gerg","Baker","1234567898"));
  book.Add(book.getRoot(),Person("Sam","Benboy","2234567891"));
  book.Add(book.getRoot(),Person("Tommy","Keegan","3234567891")); 
  book.Add(book.getRoot(),Person("George","Barker","3334567891"));
  book.Add(book.getRoot(),Person("Anna","Simonitis","5534567891"));
  book.Add(book.getRoot(),Person("Anna","Lanz","6234567891"));
  book.Display(book.getRoot());
  book.Delete(book.getRoot(),"Barker","Greg");
  //book.Delete(book.getRoot(), "Simonitis", "Anna");
  //book.Delete(book.getRoot(), "Keegan", "Tommy");
  //book.Delete(book.getRoot(), "Barker", "Greg");
  cout<<endl;
  //book.Display(book.getRoot());  
  //book.Change("Greg","Barker",5);
  //book.Display(book.getRoot());
  book.Quit(book.getRoot(),outfile);
  outfile.close();
  ifstream infile;
  infile.open("PhoneBook.txt");
  book.Restore(infile);
  infile.close();
  return 0;
}