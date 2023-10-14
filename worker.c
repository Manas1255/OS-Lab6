#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int calculate(int operand1, int operand2, char operator) {
    switch (operator) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 != 0) {
                return operand1 / operand2;
            } else {
                return -1; // Handle division by zero
            }
        default:
            return -1; // Handle unknown operator
    }
}

int main() {
    const char *fifo_name = "/tmp/my_fifo";
    int data_fd;
    char input_buffer[100];
    
    // Create the named pipe (FIFO) if it doesn't exist
    mkfifo(fifo_name, 0666);

    data_fd = open(fifo_name, O_RDONLY);
    read(data_fd, input_buffer, sizeof(input_buffer));
    close(data_fd);

    char operator;
    int operand1, operand2;
    sscanf(input_buffer, "%c %d %d", &operator, &operand1, &operand2);

    int result = calculate(operand1, operand2, operator);

    // Open another FIFO for sending the result
    int result_fd = open(fifo_name, O_WRONLY);
    char result_buffer[100];
    snprintf(result_buffer, sizeof(result_buffer), "%d", result);
    write(result_fd, result_buffer, strlen(result_buffer) + 1);
    close(result_fd);

    return 0;
}