/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:10:07 by roalexan          #+#    #+#             */
/*   Updated: 2024/11/23 19:31:14 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putstr_fd(char *s, int *count)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_print_char(s[i], count);
		i++;
	}
}

void	ft_print_str(char *s, int *count)
{
	if (!s)
	{
		ft_putstr_fd("(null)", count);
		return ;
	}
	else
	{
		while (*s)
			ft_print_char(*s++, count);
	}
}
