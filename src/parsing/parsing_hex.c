/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:46:17 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/24 17:54:00 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

int	is_upper_hex_char(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'A' && c <= 'F')
		return (1);
	return (0);
}

int	hex_char_to_int(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	return (c - 'A' + 10);
}

unsigned int	hex_to_int(char *hex)
{
	int				i;
	unsigned int	result;

	i = 0;
	result = 0;
	while (hex[i] != '\0')
	{
		if (!is_upper_hex_char(hex[i]))
			return (-1);
		result = result * 16 + hex_char_to_int(hex[i]);
		i = i + 1;
	}
	return (result);
}
