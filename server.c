#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

int main(void)
{
    int server_socket;
    struct sockaddr_in server_address = {0};

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == -1) {
        perror("socket");
        return 1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);

    if (bind(
            server_socket,
            (struct sockaddr *)&server_address,
            sizeof(server_address)
        ) == -1) {
        perror("bind");
        close(server_socket);
        return 1;
    }

    printf("Socket bound to port %d\n", PORT);

    close(server_socket);

    return 0;
}