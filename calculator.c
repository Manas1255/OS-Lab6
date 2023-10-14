#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    const char *fifo_name = "/tmp/my_fifo";
    int data_fd;
    int read_fd;
    int num_elements = 5; // Change this to match the number of elements in your array
    int received_array[5];

    // Open the named pipe (FIFO) for reading
    data_fd = open(fifo_name, O_RDONLY);

    while (1) {
        // Receive the integer array from handler.c
        read(data_fd, received_array, sizeof(int) * num_elements);

        // Calculate the sum
        int sum = 0;
        for (int i = 0; i < num_elements; i++) {
            sum += received_array[i];
        }

        // Send the sum back to handler.c
        read_fd = open(fifo_name, O_WRONLY);
        write(read_fd, &sum, sizeof(int));
        close(read_fd);

        // Exit the loop
        break;
    }

    close(data_fd);

    return 0;
}