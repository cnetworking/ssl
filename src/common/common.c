#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#include "common.h"

int file_count(char filename[MAX_FILE_NAME]) {
    FILE *fp;
    int count = 0;
    char c;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("could not open file %s\n", filename);
        return -1;
    }
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n')
            count = count + 1;

    fclose(fp);
    return count;
}

void remove_newline(char *s) {
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '\n') {
            s[i] = '\0';
        }
    }
}

int to_int(char stringNumber[]) {
    // 1.
    if (!stringNumber) {
        printf("parameter error\n");
        return -1;
    }
    char numberSign = stringNumber[0];
    int isPositive = 1;
    int number = 0;
    int i = 0;

    // 2.
    if (numberSign < '0') {
        if (numberSign == '-') {
            isPositive = 0;
            i++;
        } else {
            printf("number sign error: '%c'\n", numberSign);
            return -1;
        }
    }

    // 3.
    int stringLength = strlen(stringNumber);

    while (i < stringLength) {
        int digit = stringNumber[i++] - '0';
        if (digit < 0 || digit > 9) {
            printf("Invalid character '%c' on the position '%d'\n", stringNumber[i - 1],(i - 1));
            return -1;
        }
        number *= 10;
        number += digit;
    }

    // 4.
    if (isPositive) {
        return number;
    } else {
        printf("error\n");
        return -1;
    }
}

char *get_ip(char *type) {
    int fd;
    struct ifreq ifr;
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, type, IFNAMSIZ-1);
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);
    char *ipv4 = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
    return ipv4;
}

void clear() {
    system("clear");
}

int int_len(int i) {
    return floor(log10(abs(i))) + 1;
}