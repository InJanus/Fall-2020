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
  node*left =nullptr;
};

class Book{
  private:
    node* root;
    int size;
  public:
    Book(){//constructor
      size=0;
      root=nullptr;
    } 
    //~Book(); //Destructor FIXME
    node* getRoot(){
      return root;
    }
    //Adding an entire node basically
    void Add(node* root,string first, string last,double number){
      node* temp = new node;
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
    //Delete the node I think [FIXME]
    void Delete(string first, string last){

    }
    //returns the number of the person
    double Find(node* root, string first, string last){
      if(root == nullptr)
      {
        return 0;
      }
      else
      {
        if(last.compare(root->person.last_name)== 0 && first.compare(root->person.first_name)==0)
        {
          return (root->person.phone);
        }
        else if (last.compare(root->person.last_name)<0)
        {
          return Find(root->left,first,last);
        }
        else if (last.compare(root->person.last_name)>0)
        {
          return Find(root->right,first,last);
        }
        else if (first.compare(root->person.first_name)<0)
        {
          return Find(root->left,first,last);
        }
        else if (first.compare(root->person.first_name)>0)
        {
          return Find(root->right,first,last);
        }
      }
      
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
        //FIXME some sort of error messaging// error propogation
        //return here
      }
      found->person.phone = new_number;
    }
    //dump the whole list in alphabetical order
    void Display(){
    
    }
};









int main()
{
  Book book;
  //STILL TESTING
  book.Add(book.getRoot(),"Igum","Patel",5131234569);
  book.Add(book.getRoot(),"Greg","Barker",5131234567);
  book.Add(book.getRoot(),"Brendo","Parker",5130123456);
  book.Add(book.getRoot(),"Minglio","Zarkyr",5130123455);

  return 0;
}