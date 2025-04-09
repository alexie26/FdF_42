/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:56:24 by roalexan          #+#    #+#             */
/*   Updated: 2024/03/07 16:33:26 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	char			a;
	unsigned char	*j;
	unsigned char	*d;

	i = 0;
	a = 1;
	j = (unsigned char *)dest;
	d = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		a = -1;
		j += n - 1;
		d += n - 1;
	}
	while (i < n)
	{
		*j = *d;
		j += a;
		d += a;
		i++;
	}
	return (dest);
}
