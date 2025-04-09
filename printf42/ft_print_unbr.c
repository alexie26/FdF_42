/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:54:54 by roalexan          #+#    #+#             */
/*   Updated: 2024/11/23 19:16:19 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_unbr(unsigned int num, int *count)
{
	if (num >= 10)
	{
		ft_print_unbr((num / 10), count);
	}
	ft_print_char((num % 10) + '0', count);
}
