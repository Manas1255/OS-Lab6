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
    char input_buffer[100];
    
    // Create the named pipe (FIFO) if it doesn't exist
    mkfifo(fifo_name, 0666);

    printf("Enter operator and two operands (e.g., + 4 10): ");
    fgets(input_buffer, sizeof(input_buffer), stdin);

    data_fd = open(fifo_name, O_WRONLY);
    write(data_fd, input_buffer, strlen(input_buffer) + 1);
    close(data_fd);

    // Open another FIFO for receiving the result
    int result_fd = open(fifo_name, O_RDONLY);
    char result_buffer[100];
    read(result_fd, result_buffer, sizeof(result_buffer));
    printf("Result: %s", result_buffer);

    close(result_fd);

    return 0;
}