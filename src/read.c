#include <sh.h>

void split_word(t_list *a, t_list *b)
{
	if (b)
		list_push(&g_sh.word_list, list_new(ft_strsub(g_sh.line, *((int*)a->content), *((int*)b->content) - *((int*)a->content))));
	else
		list_push(&g_sh.word_list, list_new(ft_strsub(g_sh.line, *((int*)a->content), ft_strlen(g_sh.line) - *((int*)a->content))));
}

void trim_word(t_list *e)
{
	char *s;

	s = ft_strtrim((char *)e->content);
	free(e->content);
	e->content = s;
}

int ft_iscommand(char c)
{
	return c == ';';
}

int get_word(char *line)
{
	int i;
	t_list *stack;

	i = 0;
	int *p;
	while(line[i])
	{
		if (line[i] && ft_iscommand(line[i]))
			i += 1;
		else
		{
			p = malloc(sizeof(int));
			*p = i;
			list_push(&stack, list_new(p));
			while (line[i] && !ft_iscommand(line[i]))
				i += 1;
		}
	}
	list_reduce(stack, split_word);
	list_iter(stack, list_free);
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

void print_command(t_list *e)
{
	printf("command: %d, %s\n", ((t_command *)e->content)->argc, ((t_command *)e->content)->argv[0]);
	int i = 1;
	while (((t_command *)e->content)->argv[i])
	{
		printf("\t%s\n", ((t_command *)e->content)->argv[i]);
		i += 1;
	}
	i = 0;
	while (i < FD_LIMIT)
	{
		if (i < 3 || ((t_command *)e->content)->fds[i][1] != 0)
			printf("\t%d %d\n", ((t_command *)e->content)->fds[i][0], ((t_command *)e->content)->fds[i][1]);
		i += 1;
	}
}

void word_to_commands(t_list *e)
{
	printf("word_to_commands %s\n", (char *)e->content);

	t_list *stack;
	(void)stack;
	char **s = ft_strsplit((char *)e->content, '|');
	// free(e->content);
	// e->content = create_command(42, s);
	int i = 0;

	char *_s;
	while (s[i])
	{
		_s = ft_strtrim(s[i]);
		free(s[i]);
		s[i] = _s;

		t_command *e = create_command(i, (char *[]){ _s, 0 });
		list_push(&stack, list_new(e));

		printf("-> %s\n", s[i]);
		i += 1;
	}
	list_iter(stack, print_command);
}

int _read(void)
{
	g_sh.line = "mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi";
	// if (get_next_line(STDIN_FILENO, &(g_sh.line)) == -1)
	// 	return (errno = ERR_READ);
	// if (!g_sh.line)
	// 	return (-1);

	get_word(g_sh.line);

	list_iter(g_sh.word_list, word_to_commands);

	while (42) ;
	return (0);
}
