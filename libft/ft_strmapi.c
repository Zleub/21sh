/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 00:23:43 by adebray           #+#    #+#             */
/*   Updated: 2013/12/29 15:53:12 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s2;
	int		i;

	if (s != NULL && f != NULL)
	{
		s2 = malloc(sizeof(char) * (ft_strlen(s) + 1));
		i = 0;
		while (s[i])
		{
			s2[i] = (*f)(i, s[i]);
			i = i + 1;
		}
		return (s2);
	}
	return (NULL);
}
