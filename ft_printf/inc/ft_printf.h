/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 20:25:00 by adebray           #+#    #+#             */
/*   Updated: 2016/02/19 14:10:25 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct	s_flags
{
	char		minus;
	char		plus;
	char		zero;
	char		space;
	int			width;
	int			cmp;
}				t_flags;

int				ft_printf(const char *format, ...);
void			ft_putstr(char const *s);
void			ft_putnbr(int n);
void			ft_putchar(char c);
size_t			ft_strlen(const char *s);
char			*ft_itoa(int n);
char			*ft_cutstring(char *from, char *to);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
int				ft_putoctal(unsigned int decimal);
int				ft_puthexa(long unsigned int decimal);
int				ft_put_sheum_hexa(unsigned int decimal);
t_flags			*flags_init(t_flags *flags);
void			get_flags(t_flags *flags, char *str);
int				ft_isflags(char str);
void			get_width(t_flags *flags, char str);

#endif
