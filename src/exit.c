#include <stdlib.h>
#include <unistd.h>

void				exit_msg(char *msg, int lenght)
{
	write(1, msg, lenght);
	write(1, "\n", 1);
	exit(-1);
}
