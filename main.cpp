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
#include <cmath> // for sqrt() // a^2 = b^2 + c^2
#include <cstring>
#include <fstream> // for saving file
#include <iostream>
#include <limits> // for numeric_limits
#include <vector>

// for receiving arrow key inputs
#if defined(_WIN32)
#include <conio.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <termios.h>
#endif
// using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::numeric_limits;
using std::ofstream;
using std::string;
using std::to_string;
using std::vector;

// Global scope variables
int BoardRows = 5;
int BoardColumns = 9;
int ZombieCount = 1;
char changeSettings;
vector<vector<char>> imaginaryBoard;
bool gameOn = 1;
bool playerTurn = 1;
bool alienWon = 0;
string message;
char newOrLoadGame;
char preferredInput = '1';

// epic math time a^2 = b^2 + c^2
int checkDistance(int x1, int y1, int x2, int y2) {
  float iceCream;
  int answer;
  if (x1 != x2 && y1 != y2) {
    iceCream = sqrt(abs(y2 - y1) ^ 2 + abs(x2 - x1) ^ 2);
    answer = round(iceCream);
  } else if (x1 == x2) {
    answer = abs(y2 - y1);
  } else if (y1 == y2) {
    answer = abs(x2 - x1);
  }
  return answer;
}

// Game Characters
// All Character
class Character {
public:
  int health;
  int attack;
  int range;
};

// Player
class Alien : public Character {
public:
  void move(Alien &alien, string direction);
  void display(Alien &alien);
  void setPos(int newX, int newY);
  int getX() const;
  int getY() const;

private:
  int x_, y_;
};

void Alien::move(Alien &alien, string direction) {
  int x = alien.getX();
  int y = alien.getY();
  if (direction == "up" && y != 0) {
    alien.setPos(x, y - 1);
    y--;
    imaginaryBoard[y][x] = 'A';
  } else if (direction == "down" && y != BoardRows - 1) {
    alien.setPos(x, y + 1);
    y++;
    imaginaryBoard[y][x] = 'A';
  } else if (direction == "left" && x != 0) {
    alien.setPos(x - 1, y);
    x--;
    imaginaryBoard[y][x] = 'A';
  } else if (direction == "right" && x != BoardColumns - 1) {
    alien.setPos(x + 1, y);
    x++;
    imaginaryBoard[y][x] = 'A';
  } else { // error checker
    // cout << "There is an error! Alien could not move!" << endl;
    // pf::Pause()
    alien.setPos(x, y);
    imaginaryBoard[y][x] = 'A';
    playerTurn = 0;
  }
};
void Alien::display(Alien &alien) {
  cout << "-> Alien: health = " << alien.health << ", attack = " << alien.attack
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
  int index;

  void setPos(int newX, int newY);
  void move(Alien &alien, Zombie &zombie, vector<Zombie> &zombies);
  void display(vector<Zombie> &zombies);
  int getX() const;
  int getY() const;

private:
  int x_, y_;
};

void Zombie::setPos(int newX, int newY) {
  x_ = newX;
  y_ = newY;
}
void Zombie::move(Alien &alien, Zombie &zombie, vector<Zombie> &zombies) {
  srand(time(0));
  string direction;
  for (int i = 0; i < zombies.size(); i++) {
    int x = zombies[i].getX();
    int y = zombies[i].getY();
    // remove direction where it will hit wall
    if (y == 0) {
      string directions[3] = {"down", "left", "right"};
      direction = directions[rand() % 3];
    }
    if (y == BoardRows - 1) {
      string directions[3] = {"up", "left", "right"};
      direction = directions[rand() % 3];
    }
    if (x == 0) {
      string directions[3] = {"up", "down", "right"};
      direction = directions[rand() % 3];
    }
    if (x == BoardColumns - 1) {
      string directions[3] = {"up", "down", "left"};
      direction = directions[rand() % 3];
    }
    // move zombie
    if (direction == "up" && y != 0) {
      zombies[i].setPos(x, y - 1);
      y--;
      imaginaryBoard[y][x] = (char)(zombies[i].index + 48);
    } else if (direction == "down" && y != BoardRows - 1) {
      zombies[i].setPos(x, y + 1);
      y++;
      imaginaryBoard[y][x] = (char)(zombies[i].index + 48);
    } else if (direction == "left" && x != 0) {
      zombies[i].setPos(x - 1, y);
      x--;
      imaginaryBoard[y][x] = (char)(zombies[i].index + 48);
    } else if (direction == "right" && x != BoardColumns - 1) {
      zombies[i].setPos(x + 1, y);
      x++;
      imaginaryBoard[y][x] = (char)(zombies[i].index + 48);
    } else { // error checker
      // cout << "There is an error! Zombie could not move!" << endl;
      // pf::Pause();
      // printf("Zombie %i at (%i, %i) can't move!\n", zombies[i].index,
      // zombies[i].getX(), zombies[i].getY());
      //     hits wall
      // zombies[i].move(alien, zombie, zombies);
    }
    int num = checkDistance(alien.getX(), alien.getY(), zombies[i].getX(),
                            zombies[i].getY());
    if (num <= zombies[i].range) {
      alien.health = alien.health - zombies[i].attack;
    }
  }
}
void Zombie::display(vector<Zombie> &zombies) {
  for (int i = 0; i < zombies.size(); i++) {
    printf("   Zombie %i : health = %i, attack = %i, range = %i\n",
           zombies[i].index, zombies[i].health, zombies[i].attack,
           zombies[i].range);
  }
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

// Welcome Menu
void welcomeMenu() {
  while (true) {
    pf::ClearScreen();
    cout << endl;
    cout << "+---------------------------------------------+" << endl;
    cout << "|               ALIEN VS ZOMBIE               |" << endl;
    cout << "|=============================================|" << endl;
    cout << "| Select:                                     |" << endl;
    cout << "|    1 => New Game                            |" << endl;
    cout << "|    2 => Load Game                           |" << endl;
    cout << "|---------------------------------------------|" << endl;
    cout << "|    Q => Quit                                |" << endl;
    cout << "+---------------------------------------------+" << endl;
    cout << endl;
    cout << "Choice => ";
    cin >> newOrLoadGame;
    if (newOrLoadGame == '1' || newOrLoadGame == '2') {
      pf::ClearScreen();
      break;
    } else if (toupper(newOrLoadGame) == 'Q') {
      playerTurn = 0;
      gameOn = 0;
      break;
    }
  }
}

// Game Settings
void generateGameSettings() {
  string acceptedStrings[2] = {"y", "n"};

  // Game Start UI
  cout << "Default Game Settings" << endl;
  cout << "-----------------------" << endl;
  cout << "Board Rows    : " << BoardRows << endl;
  cout << "Board Columns : " << BoardColumns << endl;
  cout << "Zombie Count  : " << ZombieCount << endl;
  cout << "Prefer Input  : " << preferredInput << endl;
  cout << "(1 - Arrow Keys, 2 - Type Commands)" << endl;
  cout << endl;
  cout << "Do you wish to change the game default settings (y/n)? => ";
  cin >> changeSettings;

  if (toupper(changeSettings) == 'Y') {
    pf::ClearScreen();
    // Receive input for input settings
    while (true) {
      cout << "Input Settings" << endl;
      cout << "----------------" << endl;
      cout << "(1 - Arrow Keys, 2 - Type Commands)" << endl;
      cout << "Input type => ";
      cin >> preferredInput;
      cout << endl;
      if (preferredInput == '1' || preferredInput == '2')
        break;
    }

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
// uncomment line 388, 390, 401, 404 to visualize imaginaryBoard
void createGameBoard(Alien &alien, Zombie &zombie, vector<Zombie> &zombies) {
  // Randomize seed
  srand(time(0));
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
  vector<char> gameObj = {' ', ' ', ' ', '^', 'v', '<', '>', 'h', 'p', 'r'};

  // Add zombies to the end of gameObj vector
  for (int i = 0; i < zombies.size(); i++) {
    // **POSSIBILITY OF BUG**:
    // random number doesnt reach the largest number and spawn less zombie
    // idea: append zombies to the front instead, and change rand() range less
    // until all zombies are spawned
    gameObj.push_back(char(zombies[i].index + 48)); // '1' is 49 in ASCII
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
      } else if (random_number >= 10 && (int)gameObj.size() >= 10) {
        // zombie code
        int num = (int)gameObj[random_number] - 49; // convert '1' to 0
        zombies[num].setPos(col, row);
        imaginaryBoard[zombies[num].getY()][zombies[num].getX()] =
            gameObj[random_number];
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

void updateGameBoard(Alien &alien, Zombie &zombie, vector<Zombie> &zombies) {
  // remove trails and regenerate game objects
  // while keeping alien and zombie location

  // Randomize seed
  srand(time(0));

  // ^ - up
  // v - down
  // < - left
  // > - right
  // h - health
  // p - pod
  // r - rock
  // add more spaces to increase chances of empty spaces
  vector<char> gameObj = {' ', ' ', ' ', '^', 'v', '<', '>', 'h', 'p', 'r'};

  // Generate Real Game Board
  imaginaryBoard.resize(BoardRows);
  for (int row = 0; row < BoardRows; ++row) {
    for (int col = 0; col < BoardColumns; ++col) {
      imaginaryBoard[row].resize(BoardColumns);

      int random_number = rand() % gameObj.size();
      int num = 0;
      if (row == alien.getY() && col == alien.getX()) {
        // spawn alien at last location
        int x = alien.getX();
        int y = alien.getY();
        imaginaryBoard[y][x] = 'A';
      } else {
        imaginaryBoard[row][col] = gameObj[random_number];
      }
      for (int i = 0; i < (int)zombies.size(); i++) {
        if (row == zombies[i].getY() &&
            col ==
                zombies[i].getX()) { //  spawn zombies at respective locations
                                     // zombie code
          imaginaryBoard[zombies[i].getY()][zombies[i].getX()] =
              (char)(zombies[i].index + 48);
        }
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
  alien.health = (rand() % 4 + 1) * 50;
  alien.attack = 0;
  alien.range = 1;
  // Create zombie attributes
  for (int i = 0; i < ZombieCount; i++) {
    zombie.index = i + 1;
    zombie.health = (rand() % 4 + 1) * 50;
    zombie.attack = (rand() % 3 + 1) * 5;
    zombie.range = rand() % 3 + 1;
    zombies.push_back(zombie);
  }
}

// Show game character attributes below game board
void showGameCharacters(Alien &alien, Zombie &zombie, vector<Zombie> &zombies) {
  alien.display(alien);
  zombie.display(zombies);
  cout << endl;
}

void checkNextBox(Alien &alien, Zombie &zombie, string &direction,
                  vector<Zombie> &zombies) {
  char whatIsInTheBox;
  int x = alien.getX();
  int y = alien.getY();
  int distance = numeric_limits<int>::max();
  int nearestZombieIndex;
  //  check what is in next box
  if (direction == "up" && y != 0) {
    whatIsInTheBox = imaginaryBoard[y - 1][x];
  } else if (direction == "down" && y < BoardRows - 1) {
    whatIsInTheBox = imaginaryBoard[y + 1][x];
  } else if (direction == "left" && x != 0) {
    whatIsInTheBox = imaginaryBoard[y][x - 1];
  } else if (direction == "right" && y < BoardColumns - 1) {
    whatIsInTheBox = imaginaryBoard[y][x + 1];
  } else {
    whatIsInTheBox = 'q';
  }
  switch (whatIsInTheBox) {
  case 'h':
    //  leave a trail
    imaginaryBoard[y][x] = '.';
    // move alien to next box
    alien.move(alien, direction);
    // increase alien health
    alien.health = alien.health + 20;
    showGameBoard();
    showGameCharacters(alien, zombie, zombies);
    printf("You picked up a health pack! Health +20!\n");
    pf::Pause();
    break;
  case 'p':
    //  leave a trail
    imaginaryBoard[y][x] = '.';
    // move alien to next box
    alien.move(alien, direction);
    // deal -10 damage to nearest zombie
    // use a^2 = b^2 + c^2 math equation to find distance
    for (int i = 0; i < zombies.size(); i++) {
      int distance_ = checkDistance(alien.getX(), alien.getY(),
                                    zombies[i].getX(), zombies[i].getY());
      if (distance_ < distance) {
        distance = distance_;
        nearestZombieIndex = zombies[i].index;
      }
    }
    zombies[nearestZombieIndex - 1].health =
        zombies[nearestZombieIndex - 1].health - 10;
    // show board
    showGameBoard();
    showGameCharacters(alien, zombie, zombies);
    // show message
    printf("You picked up a pod! Dealt -10 damage to Zombie %i\n",
           nearestZombieIndex);

    pf::Pause();
    break;
  case 'r':
    message = "Alien hits a rock! Turn ends";
    playerTurn = 0;
    break;
  case ' ':
    //  leave a trail
    imaginaryBoard[y][x] = '.';
    // move alien to next box
    alien.move(alien, direction);
    showGameBoard();
    pf::Pause();
    break;
  case '.':
    //  leave a trail
    imaginaryBoard[y][x] = '.';
    // move alien to next box
    alien.move(alien, direction);
    showGameBoard();
    pf::Pause();
    break;
  default:
    if (whatIsInTheBox == '^' || whatIsInTheBox == 'v' ||
        whatIsInTheBox == '<' || whatIsInTheBox == '>') {
      //  leave a trail
      imaginaryBoard[y][x] = '.';
      // move alien to next box
      alien.move(alien, direction);
      // increase damage
      alien.attack = alien.attack + 20;
      // show message
      showGameBoard();
      showGameCharacters(alien, zombie, zombies);
      printf("You went through an arrow! Attack +20!\n");
      pf::Pause();
      // change direction
      if (whatIsInTheBox == '^') {
        direction = "up";
      } else if (whatIsInTheBox == 'v') {
        direction = "down";
      } else if (whatIsInTheBox == '<') {
        direction = "left";
      } else if (whatIsInTheBox == '>') {
        direction = "right";
      }
    } else if ((int)whatIsInTheBox >= 49 && (int)whatIsInTheBox <= 57) {
      // attacks zombie!
      zombies[(int)whatIsInTheBox - 49].health =
          zombies[(int)whatIsInTheBox - 49].health - alien.attack;
      message = string("You attacked zombie ") +
                to_string(zombies[(int)whatIsInTheBox - 49].index) + "!\n";
      if (zombies[(int)whatIsInTheBox - 49].health <= 0) { // kills zombie
        //  leave a trail
        imaginaryBoard[y][x] = '.';
        // move alien
        alien.move(alien, direction);
        // remove zombie from zombies
        zombies.erase(zombies.begin() + ((int)whatIsInTheBox - 49));
        ZombieCount--;
        // show message
        message = string("You killed zombie ") +
                  to_string(zombies[(int)whatIsInTheBox - 49].index) + "!\n";
        if (zombies.size() < 1) {
          message = message + "There are no more zombies!\n" +
                    "Congratulations, you won!\n";
          playerTurn = 0;
          alienWon = 1;
        }
      }
      alien.attack = 0;
      playerTurn = 0;
    } else {
      message = "Alien hits a wall! Turn ends";
      alien.attack = 0; // reset alien attack to 0
      playerTurn = 0;
    }
  }
}

void saveFile(Alien &alien, vector<Zombie> &zombies, int ZombieCount) {
  string saveFile;

  cout << "Enter the file name to save the current game: ";
  cin >> saveFile;

  ofstream fout(saveFile);

  // save imaginaryBoard dimensions
  fout << BoardColumns << ' ' << BoardRows;

  // save imaginaryBoard objects
  for (int row = 0; row < BoardRows; row++) {
    for (int col = 0; col < BoardColumns; col++) {
      fout << imaginaryBoard[row][col];
    }
  }
  fout << ' ' << endl;

  // alien attributes
  fout << alien.getX() << ' ' << alien.getY() << ' ' << alien.health << ' '
       << alien.attack << endl;

  // zombie attributes
  fout << zombies.size() << endl;

  for (int i = 0; i < zombies.size(); i++) {
    fout << zombies[i].getX() << ' ' << zombies[i].getY() << ' '
         << zombies[i].health << ' ' << zombies[i].attack << ' '
         << zombies[i].range << endl;
  }

  fout.close();
}

int loadFile(Alien &alien, vector<Zombie> &zombies, int ZombieCount) {
  int total_zombie = ZombieCount;

  string loadFile;
  cout << "Enter the file name to load: ";
  cin >> loadFile;

  ifstream fin(loadFile);

  if (fin.is_open()) {
    if (fin.good()) {
      // read board dimensions
      int board_column, board_row;
      fin >> board_column >> board_row;
      BoardColumns = board_column;
      BoardRows = board_row;

      // read board objects
      imaginaryBoard.resize(board_row);
      for (int row = 0; row < board_row; row++) {
        for (int col = 0; col < board_column; col++) {
          imaginaryBoard.resize(board_column);
          char obj;
          fin.get(obj);
          imaginaryBoard[row][col] = obj;
        }
      }

      int alien_x, alien_y, alien_health, alien_attack;
      fin >> alien_x >> alien_y >> alien_health >> alien_attack;

      alien.setPos(alien_x, alien_y);
      alien.health = alien_health;
      alien.attack = alien_attack;

      fin >> total_zombie;

      zombies.clear();

      for (int i = 0; i < total_zombie; i++) {
        int zombie_x, zombie_y, zombie_health, zombie_attack, zombie_range;
        fin >> zombie_x >> zombie_y >> zombie_health >> zombie_attack >>
            zombie_range;

        Zombie zombie;
        zombie.setPos(zombie_x, zombie_y);
        zombie.health = zombie_health;
        zombie.attack = zombie_attack;
        zombie.range = zombie_range;
        zombies.push_back(zombie);
      }
    }
  } else
    cout << "Failed to open file." << endl;

  fin.close();

  return total_zombie;
}

void receiveCommand(Alien &alien, Zombie &zombie, vector<Zombie> &zombies) {
  string command;
  if (preferredInput == '1') { // Arrow key
#if defined(_WIN32)
#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80
    cout << "<command> ";
    int c, ex;
    c = getch();
    if (c && c != 224) {
      cout << endl << "Not arrow: " << (char)c << endl;
    } else {
      switch (
          ex =
              getch()) { // small bug: as arrow key return a scan code of two
                         // characters, (0) or (224), "H", "K", "M", and "P" are
                         // misinterpreted as "Up", "Down", "Left", and "Right"
      case KEY_UP /* H */:
        command = "up"; // key up
        break;
      case KEY_DOWN /* K */:
        command = "down"; // key down
        break;
      case KEY_LEFT /* M */:
        command = "left"; // key left
        break;
      case KEY_RIGHT:      /* P */
        command = "right"; // key right
        break;
      case 'q':
        playerTurn = 0;
        gameOn = 0;
        break;
      case 's':
        cout << "\nSaving File..." << endl;
        pf::Pause();
        saveFile(alien, zombies, ZombieCount);
        cout << "Saved File!" << endl;
        playerTurn = 0;
        gameOn = 0;
        break;
      case 'h':
        printf("\nInstructions  :\n");
        printf("1. arrow keys -> Move Alien\n");
        printf("2. h -> Display Help Message\n");
        printf("3. q -> Quit Game\n");
        printf("4. s -> Save File\n");
        pf::Pause();
        pf::ClearScreen();
        showGameBoard();
        showGameCharacters(alien, zombie, zombies);
        receiveCommand(alien, zombie, zombies);
      default:
        cout << endl << (char)ex << endl; // not arrow
        break;
      }
    }
#elif defined(__linux__) || defined(__APPLE__)
// Black magic to prevent Linux from buffering keystrokes.
#define STDIN_FILENO 0
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    while (true) {
      cout << "<command> ";
      char c, d, e;
      cin >> c;
      if (c == 'q') {
        playerTurn = 0;
        gameOn = 0;
        break;
      } else if (c == 'h') {
        printf("\nInstructions  :\n");
        printf("1. arrow keys -> Move Alien\n");
        printf("2. h -> Display Help Message\n");
        printf("3. q -> Quit Game\n");
        printf("4. s -> Save File\n");
        pf::Pause();
        pf::ClearScreen();
        showGameBoard();
        showGameCharacters(alien, zombie, zombies);
        receiveCommand(alien, zombie, zombies);
      } else if (c == 's') {
        cout << "\nSaving File..." << endl;
        pf::Pause();
        saveFile(alien, zombies, ZombieCount);
        cout << "Saved File!" << endl;
        playerTurn = 0;
        gameOn = 0;
        break;
      } else if (c == 27) {
        cin >> d;
        if (d != 91) {
          cout << "\nError! Please do not press Esc!" << endl;
          cin >> c;
          cin >> d;
          cin >> e;
        } else {
          cin >> e;
        }
      } else {
        cout << "\nERROR! No Input received." << endl;
      }

      if ((c == 27) && (d == 91)) {
        if (e == 65) {
          command = "up";
          break;
        }
        if (e == 66) {
          command = "down";
          break;
        }
        if (e == 67) {
          command = "right";
          break;
        }
        if (e == 68) {
          command = "left";
          break;
        }
      }
    }
#endif

  } else if (preferredInput == '2') { // Input commands
    while (true) {
      cout << "<command> ";
      cin >> command;
      // convert string to lowercase
      for (int i = 0; i < command.length(); i++) {
        command[i] = tolower(command[i]);
      }
      if (command == "up") {
        break;
      }
      if (command == "down") {
        break;
      }
      if (command == "left") {
        break;
      }
      if (command == "right") {
        break;
      }
      if (command == "quit") {
        playerTurn = 0;
        gameOn = 0;
        break;
      } else if (command == "help") {
        printf("\nInstructions  :\n");
        printf("1. up/down/left/right -> Move Alien\n");
        printf("2. help -> Display Help Message\n");
        printf("3. quit -> Quit Game\n");
        printf("4. save -> Save File\n");
        pf::Pause();
        pf::ClearScreen();
        showGameBoard();
        showGameCharacters(alien, zombie, zombies);
        receiveCommand(alien, zombie, zombies);
      } else if (command == "save") {
        cout << "\nSaving File..." << endl;
        pf::Pause();
        saveFile(alien, zombies, ZombieCount);
        cout << "Saved File!" << endl;
        playerTurn = 0;
        gameOn = 0;
        break;
      }
    }
  }
  cout << endl;

  // step 1: check box ahead according to direction
  // step 2: if empty, repeat step 1
  // step 3: perform action, wall(out of bound)/rock = stop, health = health
  // +20, pod = attack nearest zombie -10, empty = continue go ahead
  // step 4: regenerate board, place a trail . at alien current spot after every
  // movement
  // step 5: end alien turn, start zombie turn when wall is hit
  while (playerTurn) {
    if (command == "up") {
      pf::ClearScreen();
      checkNextBox(alien, zombie, command, zombies);
      pf::ClearScreen();
    }
    if (command == "down") {
      pf::ClearScreen();
      checkNextBox(alien, zombie, command, zombies);
      pf::ClearScreen();
    }
    if (command == "left") {
      pf::ClearScreen();
      checkNextBox(alien, zombie, command, zombies);
      pf::ClearScreen();
    }
    if (command == "right") {
      pf::ClearScreen();
      checkNextBox(alien, zombie, command, zombies);
      pf::ClearScreen();
    }
    if (command == "quit") {
      cout << "Thank you for playing the game!" << endl;
      gameOn = 0;
    }
  }
}

int main() {
  // Initialize characters
  Alien alien;
  Zombie zombie;
  vector<Zombie> zombies;
  // Game start
  welcomeMenu();
  if (newOrLoadGame == '1') {
    generateGameSettings();
    createGameCharacters(alien, zombie, zombies);
    createGameBoard(alien, zombie, zombies);
  } else if (newOrLoadGame == '2') {
    createGameCharacters(alien, zombie, zombies);
    createGameBoard(alien, zombie, zombies);
    cout << "\nLoading File..." << endl;
    loadFile(alien, zombies, ZombieCount);
    cout << "\nLoaded File!" << endl;
    pf::Pause();
  }

  // create a game loop
  while (gameOn) {
    if (playerTurn == 1) {
      showGameBoard();
      showGameCharacters(alien, zombie, zombies);
      receiveCommand(alien, zombie, zombies);
    } else { // Zombie turn
      showGameBoard();
      showGameCharacters(alien, zombie, zombies);
      printf("%s\n", message.c_str());
      if (alienWon != 1) {
        printf("Zombies will start moving now!\n");
        pf::Pause();
        pf::ClearScreen();
        zombie.move(alien, zombie, zombies);
        updateGameBoard(alien, zombie, zombies);
        playerTurn = 1;
      } else {
        pf::Pause();
        gameOn = 0;
      }
    }
  }

  return 0;
}
