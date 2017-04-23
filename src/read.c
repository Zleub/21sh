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

	list_reduce(stack, split_word);
	list_iter(g_sh.word_list, trim_word);
	return (0);
}

t_command * create_command(int argc, char **argv)
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
	printf("command: %d, %s\n", c->argc, c->argv[0]);
	int i = 1;
	while (c->argv[i])
	{
		printf("\t%s\n", c->argv[i]);
		i += 1;
	}
	i = 0;
	while (i < FD_LIMIT)
	{
		if (c->fds[i][1] != 0 && i < 3)
			printf("\t%d %d\n", c->fds[i][0], c->fds[i][1]);
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
	free(e->content.str);
	while (s[i])
	{
		char *_s = ft_strtrim(s[i]);
		free(s[i]);
		s[i] = _s;

		char **argv = ft_memalloc(sizeof(char *) * 2);
		argv[0] = _s;
		argv[1] = 0;
		*acc = create_command(i, argv);
		acc = &((*acc)->next);
		i += 1;
	}
}

void print_word(t_list *e)
{
	printf("word: %s\n", e->content.str);
}

int _read(void)
{
	g_sh.line = "mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi";
	// if (get_next_line(STDIN_FILENO, &(g_sh.line)) == -1)
	// 	return (errno = ERR_READ);
	// if (!g_sh.line)
	// 	return (-1);

	get_word(g_sh.line);
	list_iter(g_sh.word_list, print_word);

	list_iter(g_sh.word_list, word_to_commands);
	list_iter(g_sh.word_list, print_command);

	while (42) ;
	return (0);
}
