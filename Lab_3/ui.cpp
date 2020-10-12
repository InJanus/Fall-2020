//include file
#include <stdio.h>
#include <iostream>
using namespace std;

int main(){
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
                //add user
                break;
            case(2):
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