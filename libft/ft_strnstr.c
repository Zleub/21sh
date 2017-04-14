/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 00:23:43 by adebray           #+#    #+#             */
/*   Updated: 2015/01/03 20:36:59 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t		i;
	size_t		j;

	i = 0;
	if (s2[0] == '\0')
		return (char*)(s1);
	while (s1[i] != '\0' && i < n)
	{
		j = 0;
		while (s1[i] == s2[j] && i < n)
		{
			i++;
			j++;
			if ((s2[j]) == '\0')
				return (char*)(&(s1[i - j]));
		}
		i++;
		i = i - j;
	}
	return (NULL);
}
