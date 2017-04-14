/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 00:23:43 by adebray           #+#    #+#             */
/*   Updated: 2013/12/03 00:22:06 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strstr(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	if (s2[0] == '\0')
		return (char*)(s1);
	while (s1[i] != '\0')
	{
		j = 0;
		while (s1[i] == s2[j])
		{
			i++;
			j++;
			if ((s2[j]) == '\0')
			{
				return (char*)(&(s1[i - j]));
			}
		}
		i++;
		i = i - j;
	}
	return (NULL);
}
