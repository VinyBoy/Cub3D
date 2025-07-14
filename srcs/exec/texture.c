/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 22:19:15 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/14 22:33:28 by vnieto-j         ###   ########.fr       */
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

void	set_img(t_exec *exec)
{
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
		error("Error\nCan't access to assets\n");
}

