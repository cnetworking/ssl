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

    char *ip = "192.168.1.231";
    int port = 3000;
    int loop = 0;
    char *cert_name = "keys/cert/certificate.pem";
    char *private_key_name = "keys/cert/key.pem";
    
    // Create the client socket
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        printf("error creating socket\n");
        exit(-1);
    }
    
    // Init SSL
    SSL_CTX *sslctx;
    SSL *c_ssl;
    initialize_ssl();

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

        // Do that ssl stuff
        sslctx = SSL_CTX_new(SSLv23_server_method());
        SSL_CTX_set_options(sslctx, SSL_OP_SINGLE_DH_USE);

        int use_cert = SSL_CTX_use_certificate_file(sslctx, cert_name , SSL_FILETYPE_PEM);
        int use_prv = SSL_CTX_use_PrivateKey_file(sslctx, private_key_name, SSL_FILETYPE_PEM);

        c_ssl = SSL_new(sslctx);
        SSL_set_fd(c_ssl, client_socket);
        
        // Here is the SSL Accept portion. Now all reads and writes must use SSL
        int ssl_err = SSL_accept(c_ssl);
        if (ssl_err <= 0) {
            //Error occurred, log and close down ssl
            printf("ssl error\n");
            shutdown_ssl(c_ssl);
            exit(-1);
        } else {
            // Write to the server
            char write_buffer[256] = "hello server!\n";
            SSL_write(c_ssl, write_buffer, sizeof(write_buffer));
            printf("wrote \n%s\n to server", write_buffer);        
        }
    }

    // while (loop) {

    // }
    

    return 0;
}