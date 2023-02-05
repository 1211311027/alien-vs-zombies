// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT8L
// Names: LEE RONG YI | ABDULKAFI WALEED ABDULKAFI AL MALAMI | MOALI DOUAA
// IDs: 1211311027 | 1201102665 | 1211307919
// Emails: 1211311027@student.mmu.edu.my | 1201102665@student.mmu.edu.my |
// 1211307919@student.mmu.edu.my Phones: +60102736440 | +60183211296 |
// +60182565383
// *********************************************************

#include "pf/helper.h"
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// Global scope variables
int BoardRows;
int BoardColumns;
int ZombieCount = 1;
char changeSettings;
// Blueprint
// To be replaced when i figure out how to pass variables to helper.cpp
const int kRows = 5;
const int kCols = 9;
char Board[kRows][kCols];

// Game Characters
// All Character
class Character {
public:
  int life;
  int attack;

  Character() {
    life = rand() % 10 + 1;
    attack = rand() % life;
  }
};

// Player
class Alien : public Character {
public:
  Alien() { attack = 0; }
};
// Zombie
class Zombie : public Character {
public:
  int range;

  Zombie() { range = rand() % 10 + 1; }
};

// Game Settings
void GenerateGameSettings() {
  string acceptedStrings[2] = {"y", "n"};

  // Game Start UI
  cout << "Default Game Settings" << endl;
  cout << "-----------------------" << endl;
  cout << "Board Rows    : " << kRows << endl;
  cout << "Board Columns : " << kCols << endl;
  cout << "Zombie Count  : " << ZombieCount << endl;
  cout << endl;
  cout << "Do you wish to change the game default settings (y/n)? => ";
  cin >> changeSettings;

  if (toupper(changeSettings) == 'Y') {
    pf::ClearScreen();
    // Receive input for board rows
    int input;
    cout << "Board Settings" << endl;
    cout << "----------------" << endl;
    cout << "Enter rows => ";
    cin >> input;
    // Check if input is a number
    while (cin.fail()) {
      cout << "Invalid input. Enter a number: ";
      cin.clear();
      cin.ignore(256, '\n');
      cin >> input;
    }
    // Check if input is even
    while (input % 2 == 0) {
      cout << "Invalid input. Enter an odd number: ";
      cin >> input;
    }
    // Set new board rows
    BoardRows = input;

    // Receive input for board columns
    cout << "Enter Columns: ";
    cin >> input;
    // Check if input is a number
    while (cin.fail()) {
      cout << "Invalid input. Enter a number: ";
      cin.clear();
      cin.ignore(256, '\n');
      cin >> input;
    }
    // Check if input is even
    while (input % 2 == 0) {
      cout << "Invalid input. Enter an odd number: ";
      cin >> input;
    }
    // Set new board columns
    BoardColumns = input;
    cout << endl;

    // Receive input for zombie counts
    cout << "Zombie Settings" << endl;
    cout << "-----------------" << endl;
    cout << "Enter number of zombies => ";
    cin >> input;
    // Check if input is a number
    while (cin.fail()) {
      cout << "Invalid input. Enter a number: ";
      cin.clear();
      cin.ignore(256, '\n');
      cin >> input;
    }
    // Check if input is even
    while (input % 2 == 0) {
      cout << "Invalid input. Enter an odd number: ";
      cin >> input;
    }
    // Set new zombie counts
    ZombieCount = input;
    cout << endl;
    // Exit Game Settings config
    cout << "Settings Updated." << endl;
    pf::Pause();
    cin.get();
    pf::ClearScreen();
  } else {
    // Set board rows and columns to default settings
    BoardRows = kRows;
    BoardColumns = kCols;
    pf::ClearScreen();
  }
}

// Creates an imaginary game board, for example
// **r*r*rr*
// r**r*r**r
// r*rr*rrr*
void CreateGameBoard() {

  // ^ - up
  // v - down
  // < - left
  // > - right
  // h - health
  // p - pod
  // r - rock
  wchar_t gameObj[6] = {' ', 'h', 'p', 'r'};
  for (int row = 0; row < BoardRows; ++row) {
    for (int col = 0; col < BoardColumns; ++col) {
      int random_number = std::rand() % 2;
      if (random_number) {
        Board[row][col] = ' ';
      } else {
        Board[row][col] = 'r';
      }
    }
  }
}

// Function to be called in ShowGameBoard()
// Creates +-+-+-+-+-+-+-+- border
void CreateBorder() {
  cout << " ";
  cout << " ";
  cout << " ";
  for (int border = 0; border < BoardColumns; border++) {
    cout << "+";
    cout << "-";
  }
  cout << "+" << endl;
}

// Show game board with indentations and borders
void ShowGameBoard() {
  // Initialize a and b to calculate center of board to place Alien
  int a = BoardRows / 2;
  int b = BoardColumns / 2;
  // When imaginary board column is more than 10, Indent spaces at left side of
  // game title
  if (BoardColumns > 10) {
    for (int col = 0; col < (BoardColumns * 2 - 20) / 2 + 1; col++) {
      cout << " ";
    }
  }
  cout << " .: Alien vs Zombie :. " << endl;
  // Generate real game board
  for (int row = 0; row < BoardRows; ++row) {
    CreateBorder();
    printf(" %i ", row + 1);
    for (int col = 0; col < BoardColumns; ++col) {
      cout << "|";
      if (row == a && col == b) {
        Board[row][col] = 'A';
      }
      cout << Board[row][col];
    }
    cout << "|";
    cout << endl;
  }
  CreateBorder();

  // Add column numbers at bottom of game board
  // Second row of column numbers, for every 10 columns, show 1
  cout << "   ";
  for (int i = 0; i < BoardColumns; i++) {
    int digit = (i + 1) / 10;
    cout << " ";
    if (digit == 0)
      cout << " ";
    else
      cout << digit;
  }
  cout << endl;
  // Row of column numbers from 0 to 9
  cout << "   ";
  for (int j = 0; j < BoardColumns; j++) {
    cout << " " << (j + 1) % 10;
  }
  cout << endl;
  cout << endl;
}

// Show game character attributes below game board
void ShowGameCharacters() {
  srand(time(0));

  Alien a;
  Zombie z;

  cout << "-> Alien: life = " << a.life << ", attack = " << a.attack
       << std::endl;
  for (int i = 0; i < ZombieCount; i++) {
    printf("   Zombie %i : life = %i, attack = %i, range = %i\n", i + 1, z.life,
           z.attack, z.range);
  }
}

int main() {

  GenerateGameSettings();
  CreateGameBoard();
  ShowGameBoard();
  ShowGameCharacters();
  pf::Pause();

  return 0;
}
 