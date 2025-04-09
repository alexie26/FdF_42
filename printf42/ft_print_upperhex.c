/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_upperhex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:19:26 by roalexan          #+#    #+#             */
/*   Updated: 2024/11/23 17:56:27 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_upperhex(unsigned int num, int *count)
{
	if (num >= 16)
	{
		ft_print_upperhex((num / 16), count);
	}
	if (num % 16 < 10)
		ft_print_char((num % 16) + '0', count);
	else
		ft_print_char((num % 16) - 10 + 'A', count);
}
