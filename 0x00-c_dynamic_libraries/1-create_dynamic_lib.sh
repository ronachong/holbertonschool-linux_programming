#!/bin/bash
gcc -Wall -Werror -Wextra -pedantic -c -fPIC *.c
gcc -Wall -Werror -Wextra -pedantic -shared -fPIC -o liball.so *.o
