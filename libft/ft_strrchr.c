/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/03 00:10:46 by adebray           #+#    #+#             */
/*   Updated: 2015/01/03 20:41:58 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strrchr(const char *s, int c)
{
	int		length;
	char	*p;

	if (c == '\0')
		return (char*)(s + ft_strlen(s));
	length = ft_strlen(s) + 1;
	p = (char*)(s + ft_strlen(s));
	while (length--)
	{
		if (*p != (unsigned char)c)
			p--;
		else
			return (p);
	}
	return (NULL);
}
