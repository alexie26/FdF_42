/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:05:06 by roalexan          #+#    #+#             */
/*   Updated: 2024/11/23 17:50:43 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_hex(unsigned int num, int *count)
{
	if (num >= 16)
	{
		ft_print_hex((num / 16), count);
	}
	if (num % 16 < 10)
		ft_print_char((num % 16) + '0', count);
	else
		ft_print_char((num % 16) - 10 + 'a', count);
}
