#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    char server_ip[20];
    int server_port;

    printf("Enter the server IP address: ");
    fgets(server_ip, sizeof(server_ip), stdin);
    strtok(server_ip, "\n");

    printf("Enter the server port number: ");
    scanf("%d", &server_port);

    // Clear input buffer
    while (getchar() != '\n');

    int client_socket;
    struct sockaddr_in server_address;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error in socket creation");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &(server_address.sin_addr)) <= 0) {
        perror("Invalid server IP address");
        exit(EXIT_FAILURE);
    }

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Error in connecting to server");
        exit(EXIT_FAILURE);
    }

    char user_input[BUFFER_SIZE];
    printf("Enter a text to send to the server: ");
    fgets(user_input, sizeof(user_input), stdin);
    strtok(user_input, "\n");

    ssize_t bytes_sent = send(client_socket, user_input, strlen(user_input), 0);
    if (bytes_sent < 0) {
        perror("Error in sending data to server");
        exit(EXIT_FAILURE);
    }

    char reply[BUFFER_SIZE];
    memset(reply, 0, sizeof(reply));
    ssize_t bytes_received = recv(client_socket, reply, sizeof(reply), 0);
    if (bytes_received < 0) {
        perror("Error in receiving data from server");
    } else {
        printf("Reply from server: %s\n", reply);
    }

    close(client_socket);
    return 0;
}
