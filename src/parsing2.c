/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:23:56 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/22 20:39:50 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static double	ft_atodbl(char *s)
{
	long	integer;
	double	fraction;
	double	pow;
	int		sign;

	integer = 0;
	fraction = 0;
	sign = +1;
	pow = 1;
	while ((*s == 9 && *s <= 13) || *s == 32)
		s++;
	while (*s == '+' || *s == '-')
		if (*s++ == '-')
			sign = -sign;
	while (*s != '.' && *s)
		integer = (integer * 10) + (*s++ - 48);
	if (*s == '.')
		s++;
	while (*s)
	{
		pow /= 10;
		fraction = fraction + (*s++ - 48) * pow;
	}
	return ((integer + fraction) * sign);
}


void	handle_comma_case(t_3d *fdf, char *split, int i, int row)
{
	char	**diff_split;
	char	*color;
	
	diff_split = ft_split(split, ',');
	if (!diff_split || !diff_split[0] || !diff_split[1])
	{
		ft_putstr_fd("Error: Invalid comma format in input.\n", 2);
		exit(1);
	}
	color = diff_split[1];
	fdf[i].x = i;
	fdf[i].y = row;
	fdf[i].z = ft_atoi(diff_split[0]);
	fdf[i].color_val = ft_atodbl(color);
	fdf[i].size = get_size(diff_split);
	free(diff_split[0]);
	free(diff_split[1]);
	free(diff_split);
}

void	handle_no_comma(t_3d *fdf, char *split, int i, int row)
{
	fdf[i].x = i;
	fdf[i].y = row;
	fdf[i].z = ft_atoi(split);
	fdf[i].color_val = 0xffffffff;
}

t_3d	*special_split(t_3d *fdf, char *line, int row)
{
	char	**split;
	int		i;

	split = ft_split(line, ' ');
	
	i = 0;
	while (split[i])
	{
		if (check_for_comma(split[i]) == 1)
			handle_comma_case(fdf, split[i], i, row);
		else
			handle_no_comma(fdf, split[i], i, row);
		free(split[i]);
		i++;
	}
	free(split);
	return (fdf);
}
