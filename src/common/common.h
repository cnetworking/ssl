#ifndef COMMON_H
#define COMMON_H

#define MAX_FILE_NAME 16
#define BODY_SIZE 2048
#define HEADER_SIZE 2176

// Count the amount of lines in a file
int file_count(char filename[MAX_FILE_NAME]);

// Remove the newline from the end of a string
void remove_newline(char *s);

// Convert string to an int
int to_int(char stringNumber[]);

// Get a local ip
char *get_ip(char *type);

// Clear the screen
void clear();

// Count the length of an int
int int_len(int i);

#endif