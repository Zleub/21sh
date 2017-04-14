/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/11 06:13:33 by gbir              #+#    #+#             */
/*   Updated: 2014/06/29 13:01:10 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strndup(char *s1, int n)
{
	char	*dup;
	char	*tmp;

	if (!(dup = malloc(sizeof(char) * (n + 1))))
		return (NULL);
	tmp = dup;
	while (*s1 != '\0' && n--)
		*tmp++ = *s1++;
	*tmp = 0;
	return (dup);
}
