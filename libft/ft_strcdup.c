/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/11 06:26:38 by gbir              #+#    #+#             */
/*   Updated: 2014/06/29 12:59:19 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	st_strclen(char *s1, char c)
{
	char	*tmp;

	tmp = s1;
	while (*tmp && *tmp != c)
		++tmp;
	return (tmp - s1);
}

char		*ft_strcdup(char *s1, char c)
{
	char	*dup;
	char	*tmp;
	int		n;

	n = st_strclen(s1, c);
	if (!(dup = malloc(sizeof(char) * (n + 1))))
		return (NULL);
	tmp = dup;
	while (*s1 != '\0' && n--)
		*tmp++ = *s1++;
	*tmp = 0;
	return (dup);
}
