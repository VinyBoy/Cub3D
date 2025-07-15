/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 22:19:15 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/15 10:53:35 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_image(t_exec *exec)
{
	if (exec->assets->north->image && exec->assets->south->image
		&& exec->assets->east->image && exec->assets->west->image)
		return (1);
	return (0);
}

int	init_texture(t_exec *exec)
{
	exec->assets->north = malloc(sizeof(t_texture_mlx));
	if (!exec->assets->north)
		return (0);
	exec->assets->east = malloc(sizeof(t_texture_mlx));
	if (!exec->assets->east)
		return (0);
	exec->assets->west = malloc(sizeof(t_texture_mlx));
	if (!exec->assets->west)
		return (0);
	exec->assets->south = malloc(sizeof(t_texture_mlx));
	if (!exec->assets->south)
		return (0);
	ft_memset(exec->assets->north, 0, sizeof(t_texture_mlx));
	ft_memset(exec->assets->east, 0, sizeof(t_texture_mlx));
	ft_memset(exec->assets->west, 0, sizeof(t_texture_mlx));
	ft_memset(exec->assets->south, 0, sizeof(t_texture_mlx));
	return (1);
}

int	set_img(t_exec *exec)
{
	if (!init_texture(exec))
		return (error("Error\nMalloc error texture\n"), 0);
	exec->assets->north->image = mlx_xpm_file_to_image(exec->mlx,
			exec->assets->path_no, &exec->assets->img_width,
			&exec->assets->img_height);
	exec->assets->south->image = mlx_xpm_file_to_image(exec->mlx,
			exec->assets->path_so, &exec->assets->img_width,
			&exec->assets->img_height);
	exec->assets->east->image = mlx_xpm_file_to_image(exec->mlx,
			exec->assets->path_ea, &exec->assets->img_width,
			&exec->assets->img_height);
	exec->assets->west->image = mlx_xpm_file_to_image(exec->mlx,
			exec->assets->path_we, &exec->assets->img_width,
			&exec->assets->img_height);
	if (!check_image(exec))
		return (error("Error\nCan't access to assets\n"), 0);
	return (1);
}

