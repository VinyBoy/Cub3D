/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:37:09 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/15 14:36:57 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_dir_plane_ew(t_exec *exec, int x, int y)
{
	if (exec->map[y][x] == 'E')
	{
		exec->player.dir_x = 1.0;
		exec->player.dir_y = 0.0;
		exec->player.plane_x = 0.0;
		exec->player.plane_y = 0.66;
	}
	else if (exec->map[y][x] == 'O')
	{
		exec->player.dir_x = -1.0;
		exec->player.dir_y = 0.0;
		exec->player.plane_x = 0.0;
		exec->player.plane_y = -0.66;
	}
	return ;
}

void	init_dir_plane(t_exec *exec, int x, int y)
{
	if (exec->map[y][x] == 'N')
	{
		exec->player.dir_x = 0.0;
		exec->player.dir_y = -1.0;
		exec->player.plane_x = 0.66;
		exec->player.plane_y = 0.0;
	}
	else if (exec->map[y][x] == 'S')
	{
		exec->player.dir_x = 0.0;
		exec->player.dir_y = 1.0;
		exec->player.plane_x = -0.66;
		exec->player.plane_y = 0.0;
	}
	init_dir_plane_ew(exec, x, y);
	return ;
}

void	init_pos_player(t_exec *exec)
{
	int	x;
	int	y;

	y = 0;
	while (exec->map[y] != NULL)
	{
		x = 0;
		while (exec->map[y][x] != '\0')
		{
			if (exec->map[y][x] == 'N' || exec->map[y][x] == 'S'
				|| exec->map[y][x] == 'E' || exec->map[y][x] == 'O')
			{
				exec->player.x = x + 0.5;
				exec->player.y = y + 0.5;
				init_dir_plane(exec, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	init_exec(t_exec *exec, t_cub *cub)
{
	exec->map = cub->assets->map;
	exec->map_width = 30;
	exec->map_height = 14;
	exec->win_height = 800;
	exec->win_width = 1400;
	exec->floor_ex = rgb_to_int(cub->assets->floor[0], cub->assets->floor[1],
			cub->assets->floor[2]);
	exec->ceiling_ex = rgb_to_int(cub->assets->ceiling[0],
			cub->assets->ceiling[1], cub->assets->ceiling[2]);
	exec->assets = cub->assets;
	exec->show_minimap = 0;
	init_pos_player(exec);
}

void	ft_exec(int argc, char **argv, t_cub *cub)
{
	t_exec	exec;

	(void)argc;
	(void)argv;
	init_exec(&exec, cub);
	if (!init_mlx(&exec))
		return (free_exec_exit(&exec));
}

/*
	idees :

	etant donnee que l'image doit s'adapter a la map
		->creer une fonction qui va lire les lignes horizontales et verticale
			->ajuster win->height et win->height avant la mlx_loop

*/