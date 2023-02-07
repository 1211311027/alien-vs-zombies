// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT8L
// Names: LEE RONG YI | ABDULKAFI WALEED ABDULKAFI AL MALAMI | MOALI DOUAA
// IDs: 1211311027 | 1201102665 | 1211307919
// Emails: 1211311027@student.mmu.edu.my | 1201102665@student.mmu.edu.my |
// 1211307919@student.mmu.edu.my
// Phones: +60102736440 | +60183211296 | +60182565383
// *********************************************************

#include "pf/helper.h"
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

// Global scope variables
int BoardRows = 5;
int BoardColumns = 9;
int ZombieCount = 1;
char changeSettings;
vector<vector<char>> imaginaryBoard;

// Game Characters
// All Character
class Character {
public:
  int life;
  int attack;
  int range;
};

// Player
class Alien : public Character {
public:
  Alien() {
    life = 100;
    attack = 0;
  }
};
// Zombie
class Zombie : public Character {
public:
  Zombie() { // problem: multiple zombies share the same attributes
    srand(time(0));
    life = (rand() % 5 + 1) * 50;
    attack = (rand() % 3 + 1) * 5;
    range = rand() % 10 + 1;
  }
};

// Game Objects
struct gameObj {
  string space;
  wchar_t up;
  wchar_t down;
  wchar_t left;
  wchar_t right;
  wchar_t health;
  wchar_t pod;
  wchar_t rock;
};
gameObj gameObj = {" ", '^', 'v', '<', '>', 'h', 'p', 'r'};
// access it with gameObj.health for example, to replace objects in board

// Game Settings
void GenerateGameSettings() {
  string acceptedStrings[2] = {"y", "n"};

  // Game Start UI
  cout << "Default Game Settings" << endl;
  cout << "-----------------------" << endl;
  cout << "Board Rows    : 5" << endl;
  cout << "Board Columns : 9" << endl;
  cout << "Zombie Count  : 1" << endl;
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
    // Clear screen and use default settings
    pf::ClearScreen();
  }
}

// Creates an imaginary game board, for example
// **r*r*rr*
// r**rAr**r
// r*rr*rrr*
// uncomment line 180, 183, 186 to visualize imaginaryBoard
void CreateGameBoard() {
  imaginaryBoard.resize(BoardRows);
  srand(time(0));
  // Initialize a and b to calculate center of board to place Alien
  int a = BoardRows / 2;
  int b = BoardColumns / 2;

  // ^ - up
  // v - down
  // < - left
  // > - right
  // h - health
  // p - pod
  // r - rock
  char gameObj[8] = {' ', '^', 'v', '<', '>', 'h', 'p', 'r'};
  for (int row = 0; row < BoardRows; ++row) {
    for (int col = 0; col < BoardColumns; ++col) {
      imaginaryBoard[row].resize(BoardColumns);
      int random_number = rand() % 7;
      if (row == a && col == b) {
        imaginaryBoard[row][col] = 'A';
        // cout << imaginaryBoard[row][col];
      } else {
        imaginaryBoard[row][col] = gameObj[random_number];
        // cout << imaginaryBoard[row][col];
      }
    }
    // cout << endl;
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
  // When imaginary board column is more than 10,
  // Indent spaces at left side of game title
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
      cout << imaginaryBoard[row][col];
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
  srand(time(NULL));

  Alien a;
  Zombie z;

  cout << "-> Alien: life = " << a.life << ", attack = " << a.attack
       << std::endl;
  for (int i = 0; i < ZombieCount; i++) {
    a.life = (rand() % 5 + 1) * 50;
    a.attack = (rand() % 3 + 1) * 5;
    a.range = rand() % 10 + 1;
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
