#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../common/common.h"

void serverbox(int port) {
    // Just some code to print this pretty little box
    char *ipv4 = get_ip("en0");
    int ipv4_size = strlen(ipv4);
    int ip_spaces = 18 - ipv4_size;
    
    int port_size = int_len(port);
    int p_spaces = abs(18 - port_size);

    clear();
    printf("# # # # # # # # # # # # # # # # # # # #\n");
    printf("#           SERVER INITIATED          #\n");
    printf("#           PORT   %i", port);
    for (int i = 0; i < p_spaces; i++) {
        printf(" ");
    }
    printf(" #\n");
    printf("#           IPv4   %s", ipv4);
    for (int i = 0; i < ip_spaces; i++) {
        printf(" ");
    }
    printf(" #\n");
    printf("# # # # # # # # # # # # # # # # # # # #\n");
}