#ifndef __GET_LINE_H__
#define __GET_LINE_H__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ_SIZE 1024

void test_read(const int fd);
char *_getline(const int fd);
size_t update_str(char **str_addr, char *r_addr, size_t lsize, size_t bytes_rd);
size_t expand_str(char **str_addr, size_t str_size, size_t lsize);

#endif
