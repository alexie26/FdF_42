/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:27:27 by roalexan          #+#    #+#             */
/*   Updated: 2024/11/23 19:14:48 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_hex_pointer(unsigned long c, int *count)
{
	if (c >= 16)
	{
		ft_print_hex_pointer((c / 16), count);
	}
	if (c % 16 < 10)
		ft_print_char((c % 16 + '0'), count);
	else
		ft_print_char((c % 16 - 10 + 'a'), count);
}

void	ft_print_pointer(void *p, int *count)
{
	ft_print_str("0x", count);
	ft_print_hex_pointer((unsigned long)p, count);
}
