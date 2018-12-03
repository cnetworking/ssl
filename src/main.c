#include <stdlib.h>
#include <stdio.h>

// #include <openssl/applink.c>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

/*
    https://stackoverflow.com/questions/7698488/turn-a-simple-socket-into-an-ssl-socket
*/

void initialize_ssl() {
    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();
}

void destroy_ssl() {
    ERR_free_strings();
    EVP_cleanup();
}

void shutdown_ssl() {
    SSL_shutdown(c_ssl);
    SSL_free(c_ssl);
}

int main(int argc, char **args) {
    printf("main\n");

    return 0;
}