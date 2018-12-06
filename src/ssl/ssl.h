#define SSL_H
#ifdef SSL_H

void initialize_ssl();
void destroy_ssl();
void shutdown_ssl(SSL *c_ssl);

#endif