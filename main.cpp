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
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
// using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// Global scope variables
int BoardRows = 5;
int BoardColumns = 9;
int ZombieCount = 1;
char changeSettings;
vector<vector<char>> imaginaryBoard;
bool gameOn = 1;

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
  void move(Alien &alien);
  void display(Alien &alien);
  void setPos(int newX, int newY);
  int getX() const;
  int getY() const;

private:
  int x_, y_;
};

void Alien::move(Alien &alien){

};
void Alien::display(Alien &alien) {
  cout << "-> Alien: life = " << alien.life << ", attack = " << alien.attack
       << std::endl;
}
void Alien::setPos(int newX, int newY) {
  x_ = newX;
  y_ = newY;
}
int Alien::getX() const { return x_; }
int Alien::getY() const { return y_; }

// Zombie
class Zombie : public Character {
public:
  int x, y;
  void setPos(int newX, int newY);
  void move(Zombie &zombie);
  void display(vector<Zombie> &zombies);
  int getX() const;
  int getY() const;

private:
  int x_, y_;
};

void Zombie::display(vector<Zombie> &zombies) {
  for (int i = 0; i < ZombieCount; i++) {
    printf("   Zombie %i : life = %i, attack = %i, range = %i\n", i + 1,
           zombies[i].life, zombies[i].attack, zombies[i].range);
  }
}
void Zombie::setPos(int newX, int newY) {
  x_ = newX;
  y_ = newY;
}
int Zombie::getX() const { return x_; }
int Zombie::getY() const { return y_; }

// Game Objects
struct gameObj {
  char space;
  char up;
  char down;
  char left;
  char right;
  char health;
  char pod;
  char rock;
};
gameObj gameObj = {' ', '^', 'v', '<', '>', 'h', 'p', 'r'};
// access it with gameObj.health for example, to replace objects in board

// Game Settings
void generateGameSettings() {
  string acceptedStrings[2] = {"y", "n"};

  // Game Start UI
  cout << "Default Game Settings" << endl;
  cout << "-----------------------" << endl;
  cout << "Board Rows    : " << BoardRows << endl;
  cout << "Board Columns : " << BoardColumns << endl;
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
    while (input == 0 || input > 9) {
      cout << "Invalid input. Number of zombies must be between 1 to 9."
           << endl;
      cout << "Enter number of zombies => ";
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
// uncomment line 196, 205, 208 to visualize imaginaryBoard
void createGameBoard(Alien &alien) {
  // Randomize seed
  // srand(time(0));
  // Initialize centerRow and centerColumn
  // to calculate center of board to place Alien
  int centerRow = BoardRows / 2;
  int centerColumn = BoardColumns / 2;

  // ^ - up
  // v - down
  // < - left
  // > - right
  // h - health
  // p - pod
  // r - rock
  // add more spaces to increase chances of empty spaces
  vector<char> gameObj = {' ', ' ', ' ', ' ', '^', 'v',
                          '<', '>', 'h', 'p', 'r'};
  // Add zombies
  // **POSSIBILITY OF BUG**: random number doesnt reach the largest number and
  // spawn less zombie
  for (int i = 0; i < ZombieCount; i++) {
    gameObj.push_back(char(i + 49)); // '1' is 49 in ASCII
  }
  // Generate Real Game Board
  imaginaryBoard.resize(BoardRows);
  for (int row = 0; row < BoardRows; ++row) {
    for (int col = 0; col < BoardColumns; ++col) {
      imaginaryBoard[row].resize(BoardColumns);

      int random_number = rand() % gameObj.size();
      if (row == centerRow && col == centerColumn) {
        alien.setPos(centerColumn, centerRow);
        int x = alien.getX();
        int y = alien.getY();
        // cout << centerColumn << centerRow << endl; // 4, 2
        imaginaryBoard[y][x] = 'A';
        // cout << imaginaryBoard[row][col];
      } else if (random_number >= 8 && gameObj.size() >= 8) {
        imaginaryBoard[row][col] = gameObj[random_number];
        gameObj.erase( // remove the zombie spawned from the vector
            gameObj.begin() + random_number);
      } else {
        imaginaryBoard[row][col] = gameObj[random_number];
        // cout << imaginaryBoard[row][col];
      }
    }
    //  cout << endl;
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
void showGameBoard() {
  // When imaginary board column is more than 10,
  // Indent spaces at left side of game title
  if (BoardColumns > 10) {
    for (int col = 0; col < (BoardColumns * 2 - 20) / 2 + 1; col++) {
      cout << " ";
    }
  }
  cout << "  .: Alien vs Zombie :." << endl;
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

void createGameCharacters(Alien &alien, Zombie &zombie,
                          vector<Zombie> &zombies) {
  srand(time(0));
  // Create alien attributes
  alien.life = (rand() % 4 + 1) * 50;
  alien.attack = 0;
  alien.range = 1;
  // Create zombie attributes
  for (int i = 0; i < ZombieCount; i++) {
    zombie.life = (rand() % 4 + 1) * 50;
    zombie.attack = (rand() % 3 + 1) * 5;
    zombie.range = rand() % 5 + 1;
    zombies.push_back(zombie);
  }
}

// Show game character attributes below game board
void showGameCharacters(Alien &alien, Zombie &zombie, vector<Zombie> &zombies) {
  alien.display(alien);
  zombie.display(zombies);
  cout << endl;
}

void checkNextBox(Alien &alien, string direction) {
  char whatIsInTheBox;
  string arrows = "^v<>";
  vector<char> arrow(arrows.c_str(), arrows.c_str() + arrows.size() + 1);
  int x = alien.getX();
  int y = alien.getY();
  //  check what is in next box
  // cout << "Testing..." << endl;
  // printf("Really testing....\n");
  // printf("Alien coordinate: (%i, %i)\n", x, y);
  // cout << "What is in box above Alien: " << imaginaryBoard[y - 1][x] << endl;
  whatIsInTheBox = imaginaryBoard[y - 1][x];
  switch (whatIsInTheBox) {
  case 'h':
    cout << "This is a health!" << endl;
    break;
  case 'p':
    cout << "This is a pod!" << endl;
    break;
  case 'r':
    cout << "This is a rock!" << endl;
    break;
  default:
    if (whatIsInTheBox == '^' || whatIsInTheBox == 'v' ||
        whatIsInTheBox == '<' || whatIsInTheBox == '>') {
      cout << "This is an arrow! Arrow of " << whatIsInTheBox << endl;
    } else {
      cout << "There is nothing!" << endl;
    }
    break;
  }
  pf::Pause();
  // if (imaginaryBoard[row][col - 1] == '^') {
  // cout << "It is an up arrow above me! -Alien" << endl;
  //} else {
  // cout << "It is something else!" << endl;
  //};
}

void updateGameBoard(){
    // updates imaginaryBoard
};

void receiveCommand(Alien &alien) {
  string command;
  cout << "<command> ";
  cin >> command;
  cout << endl;

  // step 1: check box above and perform action, wall(out of bound) = stop,
  // health = health +20, pod = attack nearest zombie -10, empty = continue go
  // up
  // step 2: regenerate board, place a trail . at alien current spot after
  // every movement
  // step 3: if empty, repeat step 1 & 2
  // step 4: end alien turn, start zombie turn when wall is hit
  if (command == "up") {
    cout << "Alien is moving up!" << endl;
    pf::Pause();
    checkNextBox(alien, "up");
    pf::ClearScreen();
  }
  if (command == "down") {
    cout << "Alien is moving down!" << endl;
    pf::Pause();
    checkNextBox(alien, "down");
    pf::ClearScreen();
  }
  if (command == "left") {
    cout << "Alien is moving to the left!" << endl;
    pf::Pause();
    checkNextBox(alien, "left");
    pf::ClearScreen();
  }
  if (command == "right") {
    cout << "Alien is moving to the right!" << endl;
    pf::Pause();
    checkNextBox(alien, "right");
    pf::ClearScreen();
  }
  if (command == "quit") {
    cout << "Thank you for playing the game!" << endl;
    gameOn = 0;
  }
}

int main() {
  // Initialize characters
  Alien alien;
  Zombie zombie;
  vector<Zombie> zombies;
  // create a game loop
  generateGameSettings();
  createGameBoard(alien);
  createGameCharacters(alien, zombie, zombies);
  while (gameOn) {
    showGameBoard();
    showGameCharacters(alien, zombie, zombies);
    receiveCommand(alien);
  }

  return 0;
}
