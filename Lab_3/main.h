//ignore

#include <string>
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
        Book();
        node* getRoot();
        void Add(node*, string, string, double);
        void Delete(string, string);
        double Find(node*, string, string);
        node* Search(node*, string, string);
        void Change(string, string, double);
        void Display();
};