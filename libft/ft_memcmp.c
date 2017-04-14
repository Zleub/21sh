/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 00:23:42 by adebray           #+#    #+#             */
/*   Updated: 2014/06/29 12:54:23 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*tmp;
	unsigned char	*tmp2;

	tmp = (unsigned char*)s1;
	tmp2 = (unsigned char*)s2;
	if (!tmp && !tmp2)
		return (0);
	while (n--)
	{
		if (*tmp != *tmp2)
			return (*tmp - *tmp2);
		tmp++;
		tmp2++;
	}
	return (0);
}
