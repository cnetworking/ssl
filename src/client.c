// https://stackoverflow.com/questions/7698488/turn-a-simple-socket-into-an-ssl-socket
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "ssl/ssl.h"

int main(int argc, char **args) {
    printf("client\n");

    char *ip = "192.168.1.245";
    int port = 3000;
    int loop = 0;
    
    // Create the client socket
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = INADDR_ANY;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(ip);

    // Make the connection to another socket
    int connection_status = connect(
      client_socket,
      (struct sockaddr *) &server_address,
      sizeof(server_address)
    );
    
    // Check connection status
    if (connection_status == -1) {
        printf("unable to create connection to server\n");
        printf("error code: %i\n", connection_status);
        exit(-1);
    } else {
        printf("connected to the server socket\n");
        loop = 1;
    }

    while (loop) {
        
    }

    return 0;
}