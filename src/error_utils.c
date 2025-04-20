/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalexan <roalexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:51:24 by roalexan          #+#    #+#             */
/*   Updated: 2025/04/20 18:48:39 by roalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_tab(void **tab, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_projection(t_fdf *fdf)
{
	if (!fdf)
		return ;
	if (fdf->two_d)
		free_tab((void **)fdf->two_d, fdf->rows);
	if (fdf->three_d)
		free_tab((void **)fdf->three_d, fdf->rows);
	free(fdf);
}

void	handle_error(const char *message)
{
	if (errno == 0)
	{
		ft_putstr_fd("FdF: ", 2);
		ft_putendl_fd((char *)message, 2);
	}
	else
		perror("FdF");
	exit(1);
}

void	clean_exit(t_fdf *fdf, int row)
{
	int	i;

	i = 0;
	while (i < row)
	{
		free(fdf->three_d[i]);
		i++;
	}
	mlx_delete_image(fdf->mlx, fdf->image);
	mlx_terminate(fdf->mlx);
	exit(0);
}
