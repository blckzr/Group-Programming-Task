#include <stdio.h>
#include <stdlib.h>

#define SIZE 13

int queue[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int front = 0;
int selected[5] = {0};   // Store the dequeued numbers
int dequeued[SIZE] = {0}; // Track dequeued numbers (1 = dequeued, 0 = not dequeued)

// Function to perform dequeue operation and mark the item as dequeued
int dequeue() {
    int data = queue[front];
    dequeued[front] = 1; // Mark this position as dequeued
    printf("Deleted %d\n", data);
    return data;
}

int main() {
    int start, interval, target = 0;

    // Input start and interval
    printf("Enter the start   : ");
    scanf("%d", &start);
    printf("Enter the interval: ");
    scanf("%d", &interval);

    // Adjust starting point (0-based index)
    front = start - 2;

    // Loop to select 5 elements
    while (target < 5) {
        int steps = 0;
        
        // Move by interval, counting only non-dequeued items
        while (steps < interval) {
            front = (front + 1) % SIZE;
            if (!dequeued[front]) { // Count only if not dequeued
                steps++;
            }
        }

        // Dequeue the element and add it to the selected array
        selected[target] = dequeue();
        target++;
    }

    // Print the selected elements
    printf("Selected elements:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", selected[i]);
    }

    return 0;
}
