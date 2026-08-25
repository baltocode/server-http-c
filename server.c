#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void)
{
    int server_socket;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == -1) {
        perror("socket");
        return 1;
    }

    printf("Socket created successfully: %d\n", server_socket);

    close(server_socket);

    return 0;
}