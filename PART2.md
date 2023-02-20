# Part 2

## Video Demo

[Video Demo](https://youtu.be/DPxIy1_dfLc).

## Minimum Requirements

### Completed

All the features completed.

1. Customize Game Settings
2. Game Dashboard
3. Game Characters (Attributes)
4. Board Dimensions
5. Zombies in Board
6. Game Objects
7. Alien Movement
8. Game Commands
9. Character's Turns
10. Health Object
11. Board border & Trail Reset
12. Zombie's Movement & Attack
13. Rock Object
14. Zombie Attacks Alien
15. Pod Object
16. Alien Accumulate Attacks
17. Arrow Object
18. Alien hits Zombie
19. Trail Reset
20. Alien kills Zombie and Win
21. Play Again?
22. Combo Attack
23. Save Game
24. Quit Game
25. Load Game

## Additional Features

1. Movement with arrow keys, by default the game will now receive arrow key key_down event as inputs
2. Add save/load game as welcome menu page before the game starts

## Contributions

Contribution of each group members.

### Lee Rong Yi

5. Zombies in Board
6. Game Commands
7. Board border & Trail Reset
8. Zombie Attacks Alien
9. Arrow Object
10. Alien kills Zombie and Win
11. Save Game
12. Load Game

### Moali Douaa

6. Game Objects
7. Character's Turns
8. Zombie's Movement & Attack
9. Pod Object
10. Alien hits Zombie
11. Play Again?
12. Quit Game

### Abdulkafi Waleed Abdulkafi Al Malami

7. Alien Movement
8. Health Object
9. Rock Object
10. Alien Accumulate Attacks
11. Trail Reset
12. Combo Attack

## Problems Encountered & Solutions

Describe the problems encountered and provide the solutions / plan for the solutions.

1. Generation of zombies in board is appending number of zombies to the end of an array of game objects,
   and accessing each item in the array by a random number, if the array index hits a zombie, it will spawn that zombie,
   and remove the specific zombie from the array using erase()
   It is possible that the random number generated does not hit the zombie. This would make the zombies spawned in the board less.
   Thus it creates "ghosting zombies".
   Plan for solution:
   solution a -> append zombies at the start of array instead, but it may also spawn a random number that does not hit the number.
   solution b -> manually spawn zombies at specific locations
   solution c -> create another random number that will be used to access zombies only, and spawn zombies at certain intervals

2. On Linux/MacOS, when input type 1 is set (arrow key input), during save game it does not take backspaces as input, player has to type the filename accurately
   Plan for solution:
   solution a -> temporarily enable grabbing of terminal buffer when save file mode is entered
   solution b -> end the game and rerun it again, and automatically enters save file mode with input type 2

3. On Windows, when input type 1 is set (arrow key input), it does not take spacebar as input correctly
   Solved:
   solution -> call receiveCommand() again when spacebar is detected

Current Problems:

4. Load file does not work if board is too big
   After load file, zombies will be spawned as 0

5. Zombies do not detect what is in the box ahead, if zombies touch each other, it will occur error
