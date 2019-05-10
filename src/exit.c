#include <stdlib.h>
#include <unistd.h>

void	exit_msg(char *msg, int lenght)
{
	if (write(1, msg, lenght) && write(1, "\n", 1))
		exit(-1);
	exit (-2);
}
