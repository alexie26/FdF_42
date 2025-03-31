/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:19:05 by roalexan          #+#    #+#             */
/*   Updated: 2024/12/07 18:36:19 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

size_t	gnl_strlen(const char *str);
char	*gnl_strchr(const char *str, int n);
char	*gnl_strjoin(const char *str1, const char *str2);
char	*gnl_strdup(const char *s1);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
void	*gnl_calloc(unsigned int count, unsigned int size);

char	*read_bytes(int fd, char *full_read);
char	*ft_extract_line(char *buffer);
char	*ft_next(char *buffer);
char	*get_next_line(int fd);

#endif