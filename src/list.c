#include <sh.h>

/*
** list management utils
*/

void list_free_content(t_list *list)
{
	free(list->content.str);
	free(list);
}
void list_free(t_list *list)
{
	free(list);
}

/*
** list primitive
*/

t_list *list_new(union u_sh content)
{
	t_list *n;

	n = ft_memalloc(sizeof(t_list));
	n->content = content;
	return (n);
}

void list_push(t_list **list, t_list *new)
{
	t_list *lst;

	lst = *list;
	if (!(*list))
	{
		*list = new;
		return ;
	}
	while (lst->next)
		lst = lst->next;
	lst->next = new;
}

void list_iter(t_list *list, void(*f)(t_list*))
{
	t_list *next;
	while (list)
	{
		next = list->next;
		f(list);
		list = next;
	}
}

void list_fold_left(t_list *list, void(*f)(t_list*, t_list *))
{
	while (list)
	{
		f(list, list->next);
		list = list->next;
	}
}
