/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:21:11 by roalexan          #+#    #+#             */
/*   Updated: 2024/12/07 17:50:37 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strchr(const char *str, int n)
{
	int	len;
	int	i;

	len = gnl_strlen(str) + 1;
	i = 0;
	while (i < len)
	{
		if (str[i] == (char)n)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}

char	*gnl_strjoin(const char *str1, const char *str2)
{
	int		i;
	int		j;
	char	*save;

	i = 0;
	j = 0;
	if (!str1 && !str2)
		return (NULL);
	save = malloc(sizeof(char) * (gnl_strlen(str1) + gnl_strlen(str2) + 1));
	if (!save)
		return (0);
	while (str1[j] != '\0')
	{
		save[i++] = str1[j++];
	}
	j = 0;
	while (str2[j] != '\0')
	{
		save[i++] = str2[j++];
	}
	save[i] = '\0';
	return (save);
}

char	*gnl_strdup(const char *s1)
{
	char	*s;
	int		i;

	s = malloc(gnl_strlen(s1) + 1);
	if (!s)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	s_len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	s_len = gnl_strlen(s);
	if ((size_t)start >= s_len)
	{
		return (gnl_strdup(""));
	}
	if (len > (s_len - start))
		len = s_len - start;
	s1 = (char *)malloc(len + 1);
	if (!s1)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		s1[i] = s[start + i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

// void	ft_bzero(void *s, unsigned int n)
// {
// 	unsigned char	*p;

// 	p = s;
// 	while (n--)
// 		*p++ = '\0';
// }

// void	*gnl_calloc(unsigned int count, unsigned int size)
// {
// 	void *pointer;
// 	unsigned char *p;

// 	pointer = malloc(count * size);
// 	if (!pointer)
// 		return (NULL);
// 	p = pointer;
// 	while (size--)
// 		*p++ = '\0';
// 	return (pointer);
// }