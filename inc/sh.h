#ifndef SH_H

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>

# include <libft.h>

# include <stdio.h>

enum e_errno
{
	ERR_READ = 256
};

# define FD_LIMIT 255

typedef struct s_command t_command;
typedef struct s_sh t_sh;
typedef struct s_list t_list;

struct s_sh
{
	char	*line;
	t_list	*word_list;
	int		command_nbr;
};

struct s_command
{
	int			argc;
	char		**argv;
	int			fds[FD_LIMIT][2];
	t_command	*next;
};

union u_sh
{
	int			i;
	char		*str;
	t_command	*command;
};

struct s_list
{
	union u_sh		content;
	struct s_list	*next;
};

extern t_sh g_sh;
extern char **environ;

void list_free(t_list *list);
void list_free_content(t_list *list);

int list_len(t_list *list);

t_list *list_new(union u_sh content);
void list_push(t_list **list, t_list *new);
void list_iter(t_list *list, void(*f)(t_list*));
void list_fold_left(t_list *list, void(*f)(t_list*, t_list *));

int _read(void);

#endif
