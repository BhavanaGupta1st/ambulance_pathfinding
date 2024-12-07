# Ambulance Path Project

This project implements `ambulancepath.c`, which calculates the optimal path for an ambulance to reach its destination quickly.

## Features

- Shortest path calculation 
- Customizable starting positions
- Path display

## How to Play

1. **Start the Game**: Run `a.exe`.
2. **Enter Your Name**: Follow the prompt.
3. **View the Map**: Default 6x6 grid.
4. **Change Starting Position**: Enter 'y' or 'n'.
    - If 'y', provide new coordinates.
5. **Find the Path**: The game finds the shortest path from 'S' to 'H'.
6. **View the Result**: Displays steps or a message if no path is found.

## Files

- `ambulancepath.c`: Main source code.
- `a.exe`: Compiled executable.
- `readme.md`: This file.

## Compilation

```sh
gcc -o a.exe ambulancepath.c
```

## Example

```plaintext
Welcome to the Ambulance Escape Game!
Please enter your name: John
Hello, John! Get ready to help the ambulance reach the hospital!

Default map (S=Start, H=Hospital, X=Blocked, .=Empty):
S . X . . .
. . X . X .
. X . . . .
. . . X . .
. X . . . .
. . . X . H

Change starting position? (y/n): n
Finding the shortest path from 'S' to 'H'!

Path found! Steps:
(0, 0) -> (1, 0) -> (2, 0) -> (3, 0) -> (4, 0) -> (5, 0) -> (5, 1) -> (5, 2) -> (5, 3) -> (5, 4) -> (5, 5)

Thank you for helping, John! Stay safe!
```

## Simulation Overview

### Objective

Determine if the ambulance can reach the hospital within a grid while avoiding obstacles.

### Key Functions

- `find_start`: Locates the starting position.
- `find_path`: Recursively finds a path to the hospital.

### Edge Cases

- No valid path
- Immediate success
- Surrounded start

### Complexity

- **Time**: Worst O(4^N), Best O(N)
- **Space**: O(N)

### Conclusion

This project demonstrates recursion's utility in pathfinding. Future improvements could include optimization techniques like BFS or Dijkstra's algorithm.

