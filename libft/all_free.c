/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbir <gbir@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/11 01:03:27 by gbir              #+#    #+#             */
/*   Updated: 2014/03/11 01:04:08 by gbir             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>

void	all_free(int nb, ...)
{
	va_list		ap;
	void		*to_free;

	to_free = NULL;
	va_start(ap, nb);
	while (nb-- > 0)
	{
		to_free = va_arg(ap, void *);
		free(to_free);
	}
	va_end(ap);
}
