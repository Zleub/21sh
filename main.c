#include <sh.h>

t_sh g_sh;

int _init(void)
{
	printf("init\n");
	return (0);
}

int _error(void)
{
	if (errno)
		printf("Error: %d\n", errno);
	return (0);
}

void print_signal(int s)
{
	printf("print_signal %d\n", s);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	// signal(SIGINT, print_signal);

	ft_bzero(&g_sh, sizeof(g_sh));

	_init();
	_read();

	_error();
	return (0);
}
