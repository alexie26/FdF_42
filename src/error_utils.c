/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:51:24 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/04 16:42:22 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

 void	*ft_free_split(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

void	ft_free_tab(void **tab, size_t len) // free 2D array
{
	size_t i;

	i = 0;
	if (!tab)
		return ;
	while (i < len)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	ft_free_tab((void **)map->grid2d, map->row);
	ft_free_tab((void **)map->grid3d, map->row);
	free(map);
}
void	free_grid2d(t_map *map, int row_allocated)
{
	int i;

	i = 0;
	while (i < row_allocated)
	{
		free(map->grid2d[i]);
	}
	free(map->grid2d);
}

void	handle_error(int status)
{
	if (status == -1)
		ft_printf("FdF: Memory allocation failed\n");
	else if (status == 1)
		ft_printf("FdF: Failed to open the file.\n");
	else if (status == 2)
		ft_printf("FdF: Wrong arguments count.\n");
	exit(EXIT_FAILURE);
}
