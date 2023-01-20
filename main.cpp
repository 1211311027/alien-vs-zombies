// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT8L
// Names: LEE RONG YI | ABDULKAFI WALEED ABDULKAFI AL MALAMI | MOALI DOUAA
// IDs: 1211311027 | 1201102665 | 1211307919
// Emails: 1211311027@student.mmu.edu.my | 1201102665@student.mmu.edu.my |
// 1211307919@student.mmu.edu.my Phones: +60102736440 | +60183211296 |
// +601825653383
// *********************************************************

// TODO: Fill in the missing information above and delete this line.

#include "pf/helper.h"
#include <iostream>
using namespace std;

int main() {

  int BoardRows = 5;
  int BoardColumns = 9;
  int Zombie = 1;
  char changeSettings;
  cout << "Default Game Settings" << endl;
  cout << "-----------------------" << endl;
  cout << "Board Rows    : " << BoardRows << endl;
  cout << "Board Columns : " << BoardColumns << endl;
  cout << "Zombie Count  : " << Zombie << endl;
  cout << endl;
  cout << "Do you wish to change the game default settings (y/n)? => ";
  cin >> changeSettings;

  if (toupper(changeSettings) == 'Y') {
    pf::ClearScreen();
    int input;
    cout << "Board Settings" << endl;
    cout << "----------------" << endl;
    cout << "Enter rows => ";
    cin >> input;
    while (cin.fail()) {
      cout << "Invalid input. Enter a number: ";
      cin.clear();
      cin.ignore(256, '\n');
      cin >> input;
    }
    BoardRows = input;
    cout << "Enter Columns: ";
    cin >> input;
    while (cin.fail()) {
      cout << "Invalid input. Enter a number: ";
      cin.clear();
      cin.ignore(256, '\n');
      cin >> input;
    }
    cout << endl;
    cout << "Zombie Settings" << endl;
    cout << "-----------------" << endl;
    BoardColumns = input;
    cout << "Enter number of zombies => ";
    cin >> input;
    while (cin.fail()) {
      cout << "Invalid input. Enter a number: ";
      cin.clear();
      cin.ignore(256, '\n');
      cin >> input;
    }
    Zombie = input;
    cout << endl;
    cout << "Settings Updated." << endl;
    pf::Pause();
    cin.get();
  }

  return 0;
}
