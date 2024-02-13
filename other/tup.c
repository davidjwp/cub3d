#include <stdio.h>

int main() {
    // Print some initial text
    printf("Line 1\n");
    printf("Line 2\n");
    printf("Line 3\n");

    // Move cursor up one line
    printf("\033[A");
    // Now we're overwriting "Line 3"
    printf("Overwritten Line 3");

    // To move up multiple lines, say 2 lines
    printf("\033[2A");
    // Now we're overwriting "Line 1"
    printf("Overwritten Line 1\n");

    return 0;
}