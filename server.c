#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define BACKLOG 5

int main(void)
{
    int server_socket;
    struct sockaddr_in server_address = {0};

    /* Crea un socket IPv4 di tipo TCP. */
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == -1) {
        perror("socket");
        return 1;
    }

    /* Prepara l'indirizzo del server. */
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);

    /* Associa il socket alla porta 8080. */
    if (bind(
            server_socket,
            (struct sockaddr *)&server_address,
            sizeof(server_address)
        ) == -1) {
        perror("bind");
        close(server_socket);
        return 1;
    }

    /* Trasforma il socket in un socket passivo, in ascolto. */
    if (listen(server_socket, BACKLOG) == -1) {
        perror("listen");
        close(server_socket);
        return 1;
    }

    printf("Server listening on port %d\n", PORT);

    close(server_socket);

    return 0;
}