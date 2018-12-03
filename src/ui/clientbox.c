#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../common/common.h"

void clientbox(char *ip, int port) {
    // Just some code to print this pretty little box
    int ip_size = strlen(ip);
    int ip_spaces = 18 - ip_size;

    int port_size = int_len(port);
    int p_spaces = abs(18 - port_size);

    clear();
    printf("# # # # # # # # # # # # # # # # # # # #\n");
    printf("#           CLIENT INITIATED          #\n");
    printf("#           PORT   %i", port);
    for (int i = 0; i < p_spaces; i++) {
        printf(" ");
    }
    printf(" #\n");
    printf("#           IP     %s", ip);
    for (int i = 0; i < ip_spaces; i++) {
        printf(" ");
    }
    printf(" #\n");
    printf("# # # # # # # # # # # # # # # # # # # #\n");
}