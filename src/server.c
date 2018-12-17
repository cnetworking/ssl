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
    printf("server\n");

    char *ip = "192.168.1.245";
    int port = 3000;

    // Create sockets and ssl instance
    int sockfd, newsockfd;
    SSL_CTX *sslctx;
    SSL *c_ssl;

    initialize_ssl();
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("error creating socket\n");
        exit(-1);
    }

    // Create the socket address
    struct sockaddr_in server_addr;
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    
    bind(
        sockfd, 
        (struct sockaddr *) &server_addr,
        sizeof(server_addr)
    );

    listen(sockfd, 5);

    newsockfd = accept(sockfd, (struct sockaddr_in *), &cli_addr, &clien);

    return 0;
}