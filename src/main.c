#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// #include <openssl/applink.c>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

/*
    https://stackoverflow.com/questions/7698488/turn-a-simple-socket-into-an-ssl-socket
*/



int main(int argc, char **args) {
    printf("main\n");

    // Create sockets and ssl instance
    int sockfd, newsockfd;
    SSL_CTX *sslctx;
    SSL *c_ssl;

    initialize_ssl();



    return 0;
}