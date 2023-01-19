// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT8L 
// Names: LEE RONG YI | ABDULKAFI WALEED ABDULKAFI AL MALAMI | MOALI DOUAA
// IDs: 1211311027 | 1201102665 | 1211307919
// Emails: 1211311027@student.mmu.edu.my | 1201102665@student.mmu.edu.my | 1211307919@student.mmu.edu.my
// Phones: +60102736440 | +60183211296 | +601825653383
// ********************************************************* 

// TODO: Fill in the missing information above and delete this line.

//#include "pf/helper.h"
#include <iostream>
using namespace std;

int main()
{

    cout << "Assignment (Part 1)" << endl;
    cout << "Let's Get Started!" << endl;

    int BoardRows = 5;
    int BoardColumns = 9;
    int Zombie = 1;
    char changeSettings;
cout << " --_--------------" << endl;
    cout << "  = Default Game Settings! =" << endl;
    cout << " _--------------_-" << endl;
    cout << "Board Rows : " << BoardRows << endl;
    cout << "Board Columns: " << BoardColumns << endl;
    cout << "Zombie Count: " << Zombie  << endl;
    cout << "Do you wish to change the game default settings (y/n)? ";
    cin >> changeSettings;

while (changeSettings == 'y' ||changeSettings == 'Y') {
    int input;
    cout << "Enter Rows: ";
    cin >> input;
    while(cin.fail()) {
        cout << "Invalid input. Enter a number: ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> input;
    }
    while(input % 2 == 0) {
        cout << "Invalid input. Enter an odd number: ";
        cin >> input;
    }
    BoardRows = input;
    cout << "Enter Columns: ";
    cin >> input;
    while(cin.fail()) {
        cout << "Invalid input. Enter a number: ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> input;
    }
    while(input % 2 == 0) {
        cout << "Invalid input. Enter an odd number: ";
        cin >> input;
    }
    BoardColumns = input;
    cout << "Enter the number of Zombie: ";
    cin >> input;
    while(cin.fail()) {
        cout << "Invalid input. Enter a number: ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> input;
    }
    while(input % 2 == 0) {
        cout << "Invalid input. Enter an odd number: ";
        cin >> input;
    }
    Zombie = input;
    cout << endl;
    cout << "Settings Updated." << endl;
    cout << "Press any key to continue." << endl;
    cin.get(); 
    return 0;
}
return 0;
}
