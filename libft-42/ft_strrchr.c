/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:40:06 by roalexan          #+#    #+#             */
/*   Updated: 2024/03/18 11:14:56 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*i;

	i = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			i = (char *)s;
		}
		s++;
	}
	if (*s == (char)c)
	{
		i = (char *)s;
	}
	return (i);
}
