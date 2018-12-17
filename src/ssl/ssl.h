#define SSL_H
#ifdef SSL_H

void initialize_ssl();
void destroy_ssl();
void shutdown_ssl(SSL *c_ssl);
int open_connection(const char *hostname, int port);

#endif