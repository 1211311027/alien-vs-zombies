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
#include <cstdlib>
#include <iostream>
using namespace std;

int BoardRows = 5;
int BoardColumns = 9;
int Zombie = 1;
char changeSettings;
// Blueprint
const int kRows = 5;
const int kCols = 9;
char Board[kRows][kCols];

void CreateBorder() {
  cout << " ";
  for (int border = 0; border < BoardColumns; border++) {
    cout << "+";
    cout << "-";
  }
  cout << "+" << endl;
}

void CreateGameBoard() {

  for (int row = 0; row < BoardRows; ++row) {
    for (int col = 0; col < BoardColumns; ++col) {
      int random_number = std::rand() % 2;
      if (random_number) {
        Board[row][col] = '*';
      }
      else {
        Board[row][col] = 'r';
      }
    }
  }
}

void ShowGameBoard() {
  int indentCol = (BoardColumns * 2 - 20) / 2;
  for (int col; col <= indentCol; col++) {
    cout << " ";
  }
  cout << ".: Alien vs Zombie :." << endl;
  for (int row = 0; row < BoardRows; ++row) {
    CreateBorder();
    cout << row + 1;
    for (int col = 0; col < BoardColumns; ++col) {
      cout << "|";
      cout << Board[row][col];
    }
    cout << "|";
    cout << endl;
  }
  CreateBorder();
  cout << "  ";
  for (int j = 0; j < BoardColumns; ++j)
  { 
      int digit = (j + 1) / 10;
      cout << " ";
      if (digit == 0)
      cout << " ";
      else 
      cout << digit;
  }
  cout << endl;
  cout << "  ";
  for (int j= 0; j < BoardColumns; ++j)
  {
      cout << " " << (j + 1) % 10;
  }
  cout << endl;
}


int main() {

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
    while (input % 2 == 0) {
      cout << "Invalid input. Enter an odd number: ";
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
    BoardColumns = input;
    cout << endl;
    cout << "Zombie Settings" << endl;
    cout << "-----------------" << endl;
    cout << "Enter number of zombies => ";
    cin >> input;
    while (cin.fail()) {
      cout << "Invalid input. Enter a number: ";
      cin.clear();
      cin.ignore(256, '\n');
      cin >> input;
    }
    while (input % 2 == 0) {
      cout << "Invalid input. Enter an odd number: ";
      cin >> input;
    }
    Zombie = input;
    cout << endl;
    cout << "Settings Updated." << endl;
    pf::Pause();
    cin.get();
    pf::ClearScreen();
  } else {
    pf::ClearScreen();
  }

  CreateGameBoard();
  ShowGameBoard();
  pf::Pause();

  return 0;
}
