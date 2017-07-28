#include "signals.h"

/**
 * handle_signal - handle SIGINT by printing the string "Gotcha! 2"
 *
 * Return: 0 on success, -1 on error
 */
int handle_signal(void)
{
	if (signal(2, signal_handler) == SIG_ERR)
		return (-1);
	return (0);
}

void signal_handler(int signum)
{
	printf("Gotcha! %i\n", signum);
}
