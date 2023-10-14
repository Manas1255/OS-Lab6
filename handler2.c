#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    const char *fifo_name = "/tmp/my_fifo";
    int data_fd;
    int read_fd;
    int num_elements = 5; // Change this to match the number of elements in your array
    int send_array[5] = {1, 2, 3, 4, 5}; // Replace with your array

    // Create the named pipe (FIFO) if it doesn't exist
    mkfifo(fifo_name, 0666);

    printf("Waiting for a process to connect...\n");
    data_fd = open(fifo_name, O_WRONLY);

    while (1) {
        printf("Sending the integer array to the calculator...\n");

        // Send the integer array to calculator.c
        write(data_fd, send_array, sizeof(int) * num_elements);

        sleep(2); // Wait for the calculator to process

        read_fd = open(fifo_name, O_RDONLY);
        int result;
        read(read_fd, &result, sizeof(int));
        printf("Received result from calculator: %d\n", result);

        close(read_fd);

        // Exit the loop
        break;
    }

    close(data_fd);
    unlink(fifo_name);
    return 0;
}