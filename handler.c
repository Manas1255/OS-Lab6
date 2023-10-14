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
    char read_buffer[100];
    char to_send_data[100];

    // Create the named pipe (FIFO) if it doesn't exist
    mkfifo(fifo_name, 0666);

    printf("Waiting for a process to connect...\n");
    data_fd = open(fifo_name, O_WRONLY);

    while (1) {
        printf("Enter a message (or 'exit' to quit): ");
        fgets(to_send_data, 100, stdin);

        if (strcmp(to_send_data, "exit\n") == 0) {
            break;
        }

        write(data_fd, to_send_data, strlen(to_send_data) + 1);

        read_fd = open(fifo_name, O_RDONLY);
        read(read_fd, read_buffer, sizeof(read_buffer));
        printf("Received from case_changer: %s", read_buffer);

        close(read_fd);
    }

    close(data_fd);
    unlink(fifo_name);
    return 0;
}