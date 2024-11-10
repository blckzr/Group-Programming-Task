// Group Members:
// Clarence Ignacio
// Gabriel Valderama 
// Jan Kevin Gerona
// Karl Joseph Logdat

#include <stdio.h>
#include <stdlib.h>

#define MAX 16

int board[MAX];
int n;

int check(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || board[i] - i == col - row || board[i] + i == col + row) {
            return 0;
        }
    }
    return 1;
}

int Nqueen(int row) {
    if (row == n) {
        printf("Solution for %d-Queens:\n", n);
        for (int i = 0; i < n; i++) {
            printf("Queen %d: Row %d, Column %d\n", i + 1, i + 1, board[i] + 1);
        }
        return 1;
    }

    for (int col = 0; col < n; col++) {
        if (check(row, col)) {
            board[row] = col;
            if (Nqueen(row + 1)) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    printf("Enter the n for the Queens problem: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid input! Please enter a number between 1 and %d.\n", MAX);
        return 1;
    }

    if (!Nqueen(0)) {
        printf("No solution for %d-Queens.\n", n);
        return 1;
    }

    return 0;
}
