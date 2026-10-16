#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define BACKLOG 5
#define BUFFER_SIZE 4096

int main(void)
{
    int server_socket;
    int client_socket;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;
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

    /* Mette il socket in ascolto. */
    if (listen(server_socket, BACKLOG) == -1) {
        perror("listen");
        close(server_socket);
        return 1;
    }

    printf("Server listening on port %d\n", PORT);
    printf("Waiting for a client...\n");

    /* Attende e accetta una connessione. */
    client_socket = accept(server_socket, NULL, NULL);

    if (client_socket == -1) {
        perror("accept");
        close(server_socket);
        return 1;
    }

    printf("Client connected successfully\n");
    printf("Waiting for the HTTP request...\n");

    /* Legge i dati inviati dal client. */
    bytes_received = recv(
        client_socket,
        buffer,
        sizeof(buffer) - 1,
        0
    );

    if (bytes_received == -1) {
        perror("recv");
        close(client_socket);
        close(server_socket);
        return 1;
    }

    if (bytes_received == 0) {
        printf("The client closed the connection without sending data\n");
    } else {
        /* Aggiunge il terminatore necessario per trattare i dati come testo. */
        buffer[bytes_received] = '\0';

        printf("\nHTTP request received:\n\n");
        printf("%s\n", buffer);
    }

    close(client_socket);
    close(server_socket);

    return 0;
}