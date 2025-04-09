/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:33:18 by roalexan          #+#    #+#             */
/*   Updated: 2024/11/23 18:49:44 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static void	ft_format_check(va_list ap, const char *format,
							int *count, size_t *c)
{
	if (format[*c] == 'c')
		ft_print_char(va_arg(ap, int), count);
	else if (format[*c] == 's')
		ft_print_str(va_arg(ap, char *), count);
	else if (format[*c] == 'd' || format[*c] == 'i')
		ft_print_nbr(va_arg(ap, int), count);
	else if (format[*c] == 'u')
		ft_print_unbr(va_arg(ap, unsigned int), count);
	else if (format[*c] == 'x')
		ft_print_hex(va_arg(ap, unsigned int), count);
	else if (format[*c] == 'X')
		ft_print_upperhex(va_arg(ap, unsigned int), count);
	else if (format[*c] == 'p')
		ft_print_pointer(va_arg(ap, void *), count);
	else if (format[*c] == '%')
		ft_print_char('%', count);
	(*c)++;
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	i;
	int		count;
	size_t	c;

	va_start(ap, format);
	i = 0;
	count = 0;
	c = ft_strlen(format);
	if (format == NULL)
		return (0);
	while (format[i] && (i < c))
	{
		if (format[i] != '%')
			ft_print_char(format[i++], &count);
		else
		{
			i++;
			ft_format_check(ap, format, &count, &i);
		}
	}
	va_end(ap);
	return (count);
}
