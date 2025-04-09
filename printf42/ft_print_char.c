/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:52:35 by roalexan          #+#    #+#             */
/*   Updated: 2024/11/23 19:27:04 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_char(int c, int *count)
{
	int	check;

	if (*count == -1)
		return ;
	check = write (1, &c, 1);
	if (check == -1)
	{
		*count = -1;
		return ;
	}
	else
		*count += check;
}
