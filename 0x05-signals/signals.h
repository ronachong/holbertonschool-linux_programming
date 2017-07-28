#ifndef SIGNAL_H
#define SIGNAL_H

#include <signal.h>
#include <stdio.h>

int handle_signal(void);
void signal_handler(int signum);

#endif
