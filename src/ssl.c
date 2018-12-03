#include <stdlib.h>
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
