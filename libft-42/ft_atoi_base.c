/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:18:33 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/22 19:34:49 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

static int	ft_digit_value(char c)
{
	if ('0' <= c && c <= '9')
		return (c - '0');
	else if ('A' <= c && c <= 'Z')
		return (c - 'A' + 10);
	else if ('a' <= c && c <= 'z')
		return (c - 'a' + 10);
	else
		return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	sign;
	int	digit;
	int	result;

	if (str_base < 2 || str_base > 36)
		return (0);
	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (*str)
	{
		digit = ft_digit_value(*str);
		if (digit == -1 || digit >= str_base)
			break ;
		result = result * str_base + digit;
		str++;
	}
	return (result * sign);
}
