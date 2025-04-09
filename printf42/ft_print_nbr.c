/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:55:45 by roalexan          #+#    #+#             */
/*   Updated: 2024/11/23 19:15:51 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_nbr(int num, int *count)
{
	if (num == -2147483648)
	{
		ft_print_str("-2147483648", count);
		return ;
	}
	if (num < 0)
	{
		ft_print_char('-', count);
		num = -num;
	}
	if (num >= 10)
	{
		ft_print_nbr((num / 10), count);
	}
	ft_print_char(num % 10 + '0', count);
}
