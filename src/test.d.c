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

int main() {
    int aPortNumber = 3000;
    int sockfd, newsockfd;
    SSL_CTX *sslctx;
    SSL *cSSL;

    InitializeSSL();
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd< 0)
    {
        //Log and Error
        return;
    }
    struct sockaddr_in saiServerAddress;
    bzero((char *) &saiServerAddress, sizeof(saiServerAddress));
    saiServerAddress.sin_family = AF_INET;
    saiServerAddress.sin_addr.s_addr = serv_addr;
    saiServerAddress.sin_port = htons(aPortNumber);

    bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    listen(sockfd,5);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    sslctx = SSL_CTX_new( SSLv23_server_method());
    SSL_CTX_set_options(sslctx, SSL_OP_SINGLE_DH_USE);
    int use_cert = SSL_CTX_use_certificate_file(sslctx, "/serverCertificate.pem" , SSL_FILETYPE_PEM);

    int use_prv = SSL_CTX_use_PrivateKey_file(sslctx, "/serverCertificate.pem", SSL_FILETYPE_PEM);

    cSSL = SSL_new(sslctx);
    SSL_set_fd(cSSL, newsockfd );
    //Here is the SSL Accept portion.  Now all reads and writes must use SSL
    ssl_err = SSL_accept(cSSL);
    if(ssl_err <= 0)
    {
        //Error occurred, log and close down ssl
        ShutdownSSL();
    }
}
