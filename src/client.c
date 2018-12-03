#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "http_server.h"

int main(int argc, char *argv[]) {
    // Parse the arguments
    int port;
    char *ip;
    if (argc < 3 || argc > 3 || to_int(argv[2]) <= 0) {
        printf("syntax: ./client.out <ip> <port>\n");
        exit(-1);
    } else {
        port = to_int(argv[2]);
        ip = argv[1];
    }
    
    // Print the client info box
    clientbox(ip, port);

    // Create the client socket
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(ip);

    // Connect to the server address
    int connection_status = connect(
      client_socket,
      (struct sockaddr *) &server_address,
      sizeof(server_address)
    );

    // Create the request
    char *request = "GET / HTTP/1.1\r\n\r\n";
    char response[HEADER_SIZE];

    // Send the request
    printf("sending response\n");
    send(client_socket, request, sizeof(request), 0);

    // Recieve the response
    recv(client_socket, &response, sizeof(response), 0);
    printf("%s\n", response);

    // Close the socket
    close(client_socket);

    return 0;
}