#ifndef SH_H

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>

# include <libft.h>

# include <stdio.h>

enum e_errno
{
	ERR_READ = 256
};

# define FD_LIMIT 255

typedef struct s_command t_command;
struct s_command
{
	int		argc;
	char	**argv;
	int		fds[FD_LIMIT][2];
};

typedef struct s_list t_list;
struct s_list
{
	void	*content;
	t_list	*next;
};

typedef struct s_sh t_sh;
struct s_sh
{
	char	*line;
	t_list	*word_list;
};

extern t_sh g_sh;

t_list *list_new(void *content);
void list_push(t_list **list, t_list *new);
void list_iter(t_list *list, void(*f)(t_list*));
void list_reduce(t_list *list, void(*f)(t_list*, t_list *));
void list_free(t_list *list);


int _read(void);

#endif
