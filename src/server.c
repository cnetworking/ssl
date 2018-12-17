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
    char *cert_name = "keys/cert/certificate.pem";
    char *private_key_name = "keys/cert/key.pem";

    // Create sockets and ssl instance
    int sockfd;
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
    server_addr.sin_addr.s_addr = INADDR_ANY;
    // server_addr.sin_addr.s_addr = inet_addr(ip);
    
    bind(
        sockfd, 
        (struct sockaddr *) &server_addr,
        sizeof(server_addr)
    );

    listen(sockfd, 5);

    // Accept the connection
    int accepted_socket = accept(sockfd, NULL, NULL);

    if (accepted_socket == -1) {
        printf("unable to accept client\n");
        exit(-1);
    } else {
        printf("accepted socket\n");
        // Do that ssl stuff
        sslctx = SSL_CTX_new(SSLv23_server_method());
        SSL_CTX_set_options(sslctx, SSL_OP_SINGLE_DH_USE);

        int use_cert = SSL_CTX_use_certificate_file(sslctx, cert_name , SSL_FILETYPE_PEM);
        int use_prv = SSL_CTX_use_PrivateKey_file(sslctx, private_key_name, SSL_FILETYPE_PEM);

        c_ssl = SSL_new(sslctx);
        SSL_set_fd(c_ssl, accepted_socket);
        printf("ssl initiated on server\n");
        
        // Here is the SSL Accept portion. Now all reads and writes must use SSL
        int ssl_err = SSL_accept(c_ssl);
        printf("ssl error server: %i\n", ssl_err);
        if (ssl_err <= 0) {
            //Error occurred, log and close down ssl
            printf("ssl error\n");
            shutdown_ssl(c_ssl);
            exit(-1);
        } else {
            while (1) {
                char read_buffer[256];
                SSL_read(c_ssl, (char *)read_buffer, sizeof(read_buffer));
                printf("client: %s", read_buffer);
            }
        }
    }


    return 0;
}