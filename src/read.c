#include <sh.h>

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

	g_sh.command_nbr += 1;
	pid_t p = fork();
	if (p >= 0)
	{
		if (p == 0) {
			printf("Child Process %d\n", getpid());

			dup2(e->fds[0][1], e->fds[0][0]);
			dup2(e->fds[1][1], e->fds[1][0]);
			dup2(e->fds[2][1], e->fds[2][0]);

			int i = 0;
			char *p = NULL;
			while (environ[i])
			{
				char **s = ft_strsplit(environ[i], '=');
				if (!ft_strcmp(s[0], "PATH"))
				{
					p = s[1];
					break ;
				}
				free(s[0]);
				free(s[1]);
				free(s);
				i += 1;
			}

			struct stat _stat;
			char **_p = ft_strsplit(p, ':');

			char *__;
			char *path;
			i = 0;
			while (_p[i])
			{
				__ = malloc( strlen(_p[i]) + 2 );
				ft_strcpy(__, _p[i]);
				ft_strcat(__, "/");

				path = ft_strjoin(__, e->argv[0]);
				if ( stat(path, &_stat) != -1 )
				{
					free(__);
					break ;
				}
				free(__);
				i += 1;
			}

			int ret = execve(path, e->argv, environ);
			if (ret == -1)
			{
				printf("errno %d -> %s\n", errno, strerror(errno));
				exit(ENOENT);
			}
		}
		else {
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
	// printf("current: (%d)\n", getpid());
	// g_sh.line = "cat auteur | cat | cat -ent ";
	// g_sh.line = "mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi";
	char *s = "prompt: > ";
	write(1, s, ft_strlen(s));
	if (get_next_line(STDIN_FILENO, &(g_sh.line)) == -1)
		return (errno = ERR_READ);
	if (!g_sh.line)
		return (-1);

	get_word(g_sh.line);
	list_iter(g_sh.word_list, print_word);

	list_iter(g_sh.word_list, word_to_commands);
	list_iter(g_sh.word_list, print_command);

	list_iter(g_sh.word_list, fork_command);

	int status = 0;
	printf("before wait\n");
	int w = wait(&status);
	if (w == -1)
		_error();

	// while (42) ;
	list_iter(g_sh.word_list, list_free_command);
	g_sh.word_list = 0;

	// printf("standard return for read loop\n");
	free(g_sh.line);
	return (_read());
	// return (0);
}
