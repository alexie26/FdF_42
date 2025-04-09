/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:31:16 by roalexan          #+#    #+#             */
/*   Updated: 2024/11/23 18:37:41 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

void	ft_print_char(int c, int *count);
void	ft_print_str(char *s, int *count);
void	ft_print_nbr(int num, int *count);
void	ft_print_unbr(unsigned int num, int *count);
void	ft_print_hex(unsigned int num, int *count);
void	ft_print_upperhex(unsigned int num, int *count);
void	ft_print_pointer(void *p, int *count);

int		ft_printf(const char *format, ...);

#endif