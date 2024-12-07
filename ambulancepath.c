#include <stdio.h>
#include <stdbool.h>

// Function to find the starting position of the ambulance ('S')
int find_start(char matrix[6][6], int *start_row, int *start_col) {
    // Iterate through the entire 6x6 matrix to find the position of 'S'
    for (int i = 0; i < 6; i++) {  // Outer loop for rows
        for (int j = 0; j < 6; j++) {  // Inner loop for columns
            if (matrix[i][j] == 'S') {  // If 'S' is found at position (i, j)
                *start_row = i;         // Set the start_row to the row of 'S'
                *start_col = j;         // Set the start_col to the column of 'S'
                return 1;               // Return 1 indicating that 'S' was found
            }
        }
    }
    return 0;  // Return 0 if 'S' is not found in the matrix
}

// Recursive function to check if a path exists from the starting point ('S') to the hospital ('H')
// Parameters: current position (row, col), matrix, visited matrix, path array, step counter
int find_path(int row, int col, char matrix[6][6], bool visited[6][6], int path[36][2], int *steps) {
    /* Base Case: If we have reached the hospital ('H') at the current position, return 1 (success)
       - When the ambulance reaches the hospital, we store the position in the path array and increment the steps count.
       - The function then returns 1, indicating that a valid path has been found. */
    if (matrix[row][col] == 'H') {
        path[*steps][0] = row; // Store the row of the hospital
        path[*steps][1] = col; // Store the column of the hospital
        (*steps)++;            // Increment the step counter for the hospital
        return 1;              // Return 1 if the hospital is found
    }

    visited[row][col] = true;  // Mark the current cell as visited
    path[*steps][0] = row;     // Store the current position in the path
    path[*steps][1] = col;     // Store the current column in the path
    (*steps)++;                // Increment the step counter

    /* Define possible moves: up, down, left, right
       We use two arrays to define the directions:
       - row_move: The change in row index for up and down movements.
       - col_move: The change in column index for left and right movements. */
    int row_move[] = {-1, 1, 0, 0};  // Array representing changes in row (up, down)
    int col_move[] = {0, 0, -1, 1};  // Array representing changes in column (left, right)

    /* Recursively check each possible move (up, down, left, right)
       We loop through each possible direction and calculate the new position.
       - For each possible direction (i = 0, 1, 2, 3 corresponding to up, down, left, right),
       - We calculate the new row and column based on the current position (row, col).
       - We ensure that the new position is valid: it must be within bounds, not blocked ('X'), and not visited. */
    for (int i = 0; i < 4; i++) {  // Loop through each possible move direction
        int new_row = row + row_move[i];  // Calculate the new row index based on the move
        int new_col = col + col_move[i];  // Calculate the new column index based on the move

        // Check if the new position is within bounds, not blocked ('X'), and not visited
        if (new_row >= 0 && new_row < 6 && new_col >= 0 && new_col < 6 &&
            matrix[new_row][new_col] != 'X' && !visited[new_row][new_col]) {
            /* If the new position is valid (not blocked, within bounds, and not visited),
               we recursively call find_path with the new position (new_row, new_col).
               - This step checks if there is a valid path from the new position to the hospital.
               - Here happens the key recursive call: */
            if (find_path(new_row, new_col, matrix, visited, path, steps)) {
                return 1;  // If a valid path is found from the new position, return 1 (success)
            }
        }
    }

    /* If no valid path is found, we backtrack by decrementing the step counter
       - This step undoes the current position from the path and marks it as unvisited so other paths can try it.
       - The function returns 0, indicating no path was found from the current position. */
    (*steps)--;  
    return 0;  // Return 0 if no valid path is found (dead end)
}

int main() {
    // Default map with the positions of 'S' (start), 'H' (hospital), 'X' (blocked), and '.' (empty space)
    char matrix[6][6] = {
        {'S', '.', 'X', '.', '.', '.'},
        {'.', '.', 'X', '.', 'X', '.'},
        {'.', 'X', '.', '.', '.', '.'},
        {'.', '.', '.', 'X', '.', '.'},
        {'.', 'X', '.', '.', '.', '.'},
        {'.', '.', '.', 'X', '.', 'H'}
    };

    bool visited[6][6] = {false};  // Initialize a 6x6 matrix to track visited cells, all set to false initially

    int start_row = -1, start_col = -1;  // Initialize variables to hold the start position of 'S'

    // Greet the player and get their name
    char name[50];
    printf("Welcome to the Ambulance Escape Game!\n");  // Excited introduction
    printf("Please enter your name: ");  // Asking for user input
    scanf("%s", name);  // Store the user's name
    printf("Hello, %s! Get ready to embark on a thrilling journey to help the ambulance reach the hospital!\n", name);  // Excited greeting

    printf("\nHere's the default map (S=Start, H=Hospital, X=Blocked, .=Empty):\n");
    // Print the default map to the console
    for (int i = 0; i < 6; i++) {  // Loop through each row of the matrix
        for (int j = 0; j < 6; j++) {  // Loop through each column of the matrix
            printf("%c ", matrix[i][j]);  // Print each character (representing a cell in the map)
        }
        printf("\n");  // Newline for the next row
    }

    // Ask the user if they want to change the starting position of the ambulance ('S')
    printf("\nWould you like to change the starting position of the ambulance? (y/n): ");
    char change_start;
    scanf(" %c", &change_start);  // Read the user's input (yes or no)

    if (change_start == 'y' || change_start == 'Y') {  // If user chooses to change the starting position
        int new_row, new_col;
        printf("Enter new starting position for the ambulance (row and column between 0 and 5): ");
        scanf("%d %d", &new_row, &new_col);  // Read the new row and column for the ambulance

        // Validate the new position
        if (new_row >= 0 && new_row < 6 && new_col >= 0 && new_col < 6 && matrix[new_row][new_col] != 'X') {
            // Update the map by setting the new position to 'S'
            matrix[start_row][start_col] = '.'; // Set the old start position back to empty
            matrix[new_row][new_col] = 'S';     // Set the new start position to 'S'
            start_row = new_row;                // Update the start_row to the new row
            start_col = new_col;                // Update the start_col to the new column
        } else {
            printf("Oops! Invalid position! Please choose a valid position that is within bounds and not blocked.\n");
        }
    }

    // Print the updated map after modification
    printf("\nHere's the updated map:\n");
    for (int i = 0; i < 6; i++) {  // Loop through each row of the matrix
        for (int j = 0; j < 6; j++) {  // Loop through each column of the matrix
            printf("%c ", matrix[i][j]);  // Print each character (representing a cell in the map)
        }
        printf("\n");  // Newline for the next row
    }

    // Find the starting position of the ambulance 'S' in the matrix
    if (!find_start(matrix, &start_row, &start_col)) {  // If 'S' is not found, exit the program
        printf("Oh no! Starting position 'S' not found in the matrix.\n");
        return 0;  // Exit the program
    }

    printf("Let's find the shortest path for the ambulance from 'S' to 'H'!\n");

    int path[36][2];    // Array to store the path coordinates (max possible steps)
    int steps = 0;      // Counter to keep track of the number of steps
    visited[start_row][start_col] = true;  // Mark the start position as visited

    // Start the pathfinding process and check if a path exists
    if (find_path(start_row, start_col, matrix, visited, path, &steps)) {
        // If a path is found, print the steps taken
        printf("\nPath to the hospital found! Here are the steps:\n");
        for (int i = 0; i < steps; i++) {
            printf("Step %d: (%d, %d)\n", i + 1, path[i][0], path[i][1]);  // Print each step's position
            }
            printf("Thank you for helping the Ambulance reach the Hospital, %s! Stay safe!\n", name);
    } else {
        printf("Sorry, no path found! The ambulance can't reach the hospital.\n");
        printf("Thank you for playing the Ambulance Escape Game, %s! Stay safe!\n", name);}
    

    return 0;  // End of the program
}

