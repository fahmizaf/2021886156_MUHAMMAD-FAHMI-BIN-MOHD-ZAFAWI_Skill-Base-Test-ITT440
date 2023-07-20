#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 2820

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[256];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Server address setup
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("192.168.241.128"); // localhost IP address
    server_addr.sin_port = htons(PORT);

    // Connect to server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error connecting");
        exit(EXIT_FAILURE);
    }

    // Receive random number from server
    recv(client_socket, buffer, sizeof(buffer), 0);
    int random_number = atoi(buffer);

    printf("Received random number from server: %d\n", random_number);

    close(client_socket);
    return 0;
}
