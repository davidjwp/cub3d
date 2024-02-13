#include <stdio.h>
#include <unistd.h>

void printProgressBar(int percentage) {
    int barWidth = 50; // Width of the progress bar in characters
    printf("[");
    int pos = (percentage * barWidth) / 100;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) printf("=");
        else if (i == pos) printf(">");
        else printf(" ");
    }
    printf("] %d %%\r", percentage);
    fflush(stdout); // Flush the output buffer to ensure the progress bar is displayed
}

int main() {
    int progress = 0;
    while (progress <= 100) {
        printProgressBar(progress);
        progress += 5; // Increment the progress
        sleep(1); // Sleep for 1 second to simulate work being done
    }
    printf("\n"); // Move to the next line after completing the progress
    return 0;
}