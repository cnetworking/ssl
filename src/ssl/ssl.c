#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <resolv.h>
#include <netdb.h>
#include <strings.h>

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "ssl.h"

void initialize_ssl() {
    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();
}

void destroy_ssl() {
    ERR_free_strings();
    EVP_cleanup();
}

void shutdown_ssl(SSL *c_ssl) {
    SSL_shutdown(c_ssl);
    SSL_free(c_ssl);
}

int open_connection(const char *hostname, int port) {
    int sd;
    struct hostent *host;
    struct sockaddr_in addr;

    if ((host = gethostbyname(hostname)) == NULL) {
        perror(hostname);
        abort();
    }
    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(long*)(host->h_addr);
    if (connect(sd, (struct sockaddr *) &addr, sizeof(addr)) != 0 ) {
        close(sd);
        perror(hostname);
        abort();
    }
    return sd;
}