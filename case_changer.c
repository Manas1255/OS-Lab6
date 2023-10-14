#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void reverseCase(char *str) {
    while (*str) {
        if (*str >= 'a' && *str <= 'z') {
            *str = *str - 32;
        } else if (*str >= 'A' && *str <= 'Z') {
            *str = *str + 32;
        }
        str++;
    }
}

int main() {
    const char *fifo_name = "/tmp/my_fifo";
    int data_fd;
    char read_buffer[100];

    // Open the named pipe (FIFO) for reading
    data_fd = open(fifo_name, O_RDONLY);

    while (1) {
        read(data_fd, read_buffer, sizeof(read_buffer));

        if (strcmp(read_buffer, "exit\n") == 0) {
            break;
        }

        // Reverse the case of the received string
        reverseCase(read_buffer);

        // Send the modified string back to handler.c
        int response_fd = open(fifo_name, O_WRONLY);
        write(response_fd, read_buffer, strlen(read_buffer) + 1);
        close(response_fd);
    }

    close(data_fd);

    return 0;
}