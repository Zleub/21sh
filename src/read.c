#include <sh.h>

struct s_notif_signal {
	int sig;
	char *sig_name;
	char *sig_descrption;
};

struct s_notif_signal	notif_array[] = {
	{ 0,     "NO_SIG",     "shoud not happen" },
	{ 1,     "SIGHUP",     "terminal line hangup" },
	{ 2,     "SIGINT",     "interrupt program" },
	{ 3,     "SIGQUIT",    "quit program" },
	{ 4,     "SIGILL",     "illegal instruction" },
	{ 5,     "SIGTRAP",    "trace trap" },
	{ 6,     "SIGABRT",    "abort program (formerly SIGIOT)" },
	{ 7,     "SIGEMT",     "emulate instruction executed" },
	{ 8,     "SIGFPE",     "floating-point exception" },
	{ 9,     "SIGKILL",    "kill program" },
	{ 10,    "SIGBUS",     "bus error" },
	{ 11,    "SIGSEGV",    "segmentation violation" },
	{ 12,    "SIGSYS",     "non-existent system call invoked" },
	{ 13,    "SIGPIPE",    "write on a pipe with no reader" },
	{ 14,    "SIGALRM",    "real-time timer expired" },
	{ 15,    "SIGTERM",    "software termination signal" },
	{ 16,    "SIGURG",     "urgent condition present on socket" },
	{ 17,    "SIGSTOP",    "stop (cannot be caught or ignored)" },
	{ 18,    "SIGTSTP",    "stop signal generated from keyboard" },
	{ 19,    "SIGCONT",    "continue after stop" },
	{ 20,    "SIGCHLD",    "child status has changed" },
	{ 21,    "SIGTTIN",    "background read attempted from control terminal" },
	{ 22,    "SIGTTOU",    "background write attempted to control terminal" },
	{ 23,    "SIGIO",      "I/O is possible on a descriptor (see fcntl(2))" },
	{ 24,    "SIGXCPU",    "cpu time limit exceeded (see setrlimit(2))" },
	{ 25,    "SIGXFSZ",    "file size limit exceeded (see setrlimit(2))" },
	{ 26,    "SIGVTALRM",  "virtual time alarm (see setitimer(2))" },
	{ 27,    "SIGPROF",    "profiling timer alarm (see setitimer(2))" },
	{ 28,    "SIGWINCH",   "Window size change" },
	{ 29,    "SIGINFO",    "status request from keyboard" },
	{ 30,    "SIGUSR1",    "User defined signal 1" },
	{ 31,    "SIGUSR2",    "User defined signal 2" }
};

void notify_signal(int sig)
{
	struct s_notif_signal *notif = &notif_array[sig];
	(void)notif;
	printf("[%d] notify_signal: %d -> %s (%s)\n", getpid(), sig, notif->sig_name, notif->sig_descrption);
}

void split_word(t_list *a, t_list *b)
{
	if (b)
		list_push(&g_sh.word_list, list_new((union u_sh)ft_strsub(g_sh.line, a->content.i, b->content.i - a->content.i)));
	else
		list_push(&g_sh.word_list, list_new((union u_sh)ft_strsub(g_sh.line, a->content.i, ft_strlen(g_sh.line) - a->content.i)));
}

void trim_word(t_list *e)
{
	char *s;

	s = ft_strtrim(e->content.str);
	free(e->content.str);
	e->content.str = s;
}

int ft_iscommand(char c)
{
	return c == ';';
}

void print_int(t_list *e)
{
	printf("%d\n", e->content.i);
}

int get_word(char *line)
{
	int i;
	t_list *stack;

	i = 0;
	stack = NULL;
	while(line[i])
	{
		if (line[i] && ft_iscommand(line[i]))
			i += 1;
		else
		{
			list_push(&stack, list_new((union u_sh)i));
			while (line[i] && !ft_iscommand(line[i]))
				i += 1;
		}
	}

	list_fold_left(stack, split_word);
	list_iter(stack, list_free);
	list_iter(g_sh.word_list, trim_word);
	return (0);
}

t_command *create_command(int argc, char **argv)
{
	t_command *e;

	e = ft_memalloc(sizeof(t_command));
	e->argc = argc;
	e->argv = argv;
	ft_bzero(e->fds, sizeof(char) * FD_LIMIT * 2 );
	e->fds[0][0] = 0;
	e->fds[0][1] = 0;
	e->fds[1][0] = 1;
	e->fds[1][1] = 1;
	e->fds[2][0] = 2;
	e->fds[2][1] = 2;
	return (e);
}

void __print_command(t_command *c)
{
	for (int i = 0; i < c->argc; i++)
		printf("  ");
	printf("command: %d, %s\n", c->argc, c->argv[0]);
	int i = 1;
	while (c->argv[i])
	{
		for (int i = 0; i < c->argc; i++)
			printf("  ");
		printf("    %s\n", c->argv[i]);
		i += 1;
	}
	i = 0;
	while (i < FD_LIMIT)
	{
		if (i < 3 || c->fds[i][1] != 0) {
			for (int i = 0; i < c->argc; i++)
				printf("  ");
			printf("    %d %d\n", c->fds[i][0], c->fds[i][1]);
		}
		i += 1;
	}
	if (c->next)
		__print_command(c->next);
}

void print_command(t_list *e)
{
	__print_command(e->content.command);
}

void word_to_commands(t_list *e)
{
	printf("word_to_commands %s\n", e->content.str);

	char **s = ft_strsplit(e->content.str, '|');
	int i = 0;
	t_command **acc = &e->content.command;
	int p[2];
	ft_bzero(p, sizeof(int) * 2);
	free(e->content.str);
	while (s[i])
	{
		char *_s = ft_strtrim(s[i]);
		char **argv = ft_strsplit(_s, ' ');
		*acc = create_command(i, argv);
		if (p[0])
			(*acc)->fds[0][1] = p[0];
		if (s[i + 1]) {
			pipe(p);
			(*acc)->fds[1][1] = p[1];
		}

		acc = &( (*acc)->next );
		free(s[i]);
		i += 1;
	}
	free(s);
}

void print_word(t_list *e)
{
	printf("word: %s\n", e->content.str);
}

void __fork_command(t_command *e)
{
	printf("fork_command %s %s\n", e->argv[0], e->argv[1]);
	// printf("B errno %d -> %s\n", errno, strerror(errno));

	errno = 0;
	pid_t p = fork();
	if (p >= 0)
	{
		if (p == 0) {
			// printf("Child Process %d\n", getpid());
			dprintf(2, "%d: dup2 %d -> %d\n", dup2(e->fds[0][1], e->fds[0][0]), e->fds[0][1], e->fds[0][0]);
			dprintf(2, "%d: dup2 %d -> %d\n", dup2(e->fds[1][1], e->fds[1][0]), e->fds[1][1], e->fds[1][0]);
			dprintf(2, "%d: dup2 %d -> %d\n", dup2(e->fds[2][1], e->fds[2][0]), e->fds[2][1], e->fds[2][0]);
			// dup2(e->fds[0][1], e->fds[0][0]);
			// dup2(e->fds[1][1], e->fds[1][0]);
			// dup2(e->fds[2][1], e->fds[2][0]);
			// signal(SIGTTOU, SIG_IGN);
			// signal(SIGTTIN, SIG_IGN);

			char s[] = "/bin/cat";
			// ft_strcat(s, e->argv[0]);
			// printf("execve %s\n", s);
			int ret = execve(s, e->argv, environ);
			if (ret == -1)
				printf("errno %d -> %s\n", errno, strerror(errno));
		}
		else {
			// int status;
			// wait(&status);
			printf("Parent process\n");
			// printf("C errno %d -> %s\n", errno, strerror(errno));
			if (e->next)
				__fork_command(e->next);
		}
	}
	else
		printf("Fork failed\n");
}

void fork_command(t_list *e)
{
	__fork_command(e->content.command);
}

int _read(void)
{
	printf("current: (%d)\n", getpid());
	g_sh.line = "cat Makefile | cat | cat -ent ";
	// g_sh.line = "mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi";
	// char *s = "prompt: >";
	// write(1, s, ft_strlen(s));
	// if (get_next_line(STDIN_FILENO, &(g_sh.line)) == -1)
	// 	return (errno = ERR_READ);
	// if (!g_sh.line)
	// 	return (-1);

	get_word(g_sh.line);
	list_iter(g_sh.word_list, print_word);

	list_iter(g_sh.word_list, word_to_commands);
	list_iter(g_sh.word_list, print_command);

	// int i = 0;
	// while (environ[i])
	// {
	// 	char **s = ft_strsplit(environ[i], '=');
	// 	if (!ft_strcmp(s[0], "PATH"))
	// 		printf("%s\n", s[1]);
	// 	free(s[0]);
	// 	free(s[1]);
	// 	free(s);
	// 	i += 1;
	// }

	errno = 0;
	// printf("-Z errno %d -> %s\n", errno, strerror(errno));
	pid_t p = fork();
	// errno = 0;
	if (p >= 0)
	{
		if (p == 0) {
			// printf("A errno %d -> %s\n", errno, strerror(errno));
			list_iter(g_sh.word_list, fork_command);
		}
		else {
			signal(SIGCHLD, notify_signal);
			// printf("test\n");
			int status = 0;
			printf("GrandFather wait %d\n", wait(&status));
			printf("Parent process %d\n", status);
			// printf("D errno %d -> %s\n", errno, strerror(errno));
		}
	}
	else
		printf("Fork failed\n");

	list_iter(g_sh.word_list, list_free_content);
	g_sh.word_list = 0;

	// printf("standard return for read loop\n");
	// while (42) ;
	// return (_read());
	return (0);
}
