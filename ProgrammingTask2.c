// Group Members:
// Clarence Ignacio
// Gabriel Valderama 
// Jan Kevin Gerona
// Karl Joseph Logdat

#include <stdio.h>
#include <stdlib.h>

#define MAX 16  // Define the maximum size of the board

int board[MAX];  // Array to store the positions of the queens
int n;  // Variable to store the size of the board (n x n)

// Function to check if placing a queen at (row, col) is safe
int check(int row, int col) {
    for (int i = 0; i < row; i++) {
        // Check columns and diagonals for conflicts
        if (board[i] == col || board[i] - i == col - row || board[i] + i == col + row) {
            return 0;  // Return 0 if there is a conflict
        }
    }
    return 1;  // Return 1 if it is safe to place the queen
}

// Recursive function to solve the n-Queens problem
int Nqueen(int row) {
    if (row == n) {
        // Print the solution if all queens are placed
        printf("Solution for %d-Queens:\n", n);
        for (int i = 0; i < n; i++) {
            printf("Queen %d: Row %d, Column %d\n", i + 1, i + 1, board[i] + 1);
        }
        return 1;  // Return 1 to indicate a solution is found
    }

    for (int col = 0; col < n; col++) {
        // Try placing a queen at each column in the current row
        if (check(row, col)) {
            board[row] = col;  // Place the queen
            if (Nqueen(row + 1)) {
                return 1;  // Return 1 if placing the queen leads to a solution
            }
        }
    }
    return 0;  // Return 0 if no valid placement is found in the current configuration
}

int main() {
    printf("Enter the n for the Queens problem: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        // Check for invalid input
        printf("Invalid input! Please enter a number between 1 and %d.\n", MAX);
        return 1;  // Exit the program if the input is invalid
    }

    if (!Nqueen(0)) {
        // Call the Nqueen function to solve the problem and check if a solution exists
        printf("No solution for %d-Queens.\n", n);
        return 1;  // Exit the program if no solution is found
    }

    return 0;  // Return 0 to indicate successful execution
}
