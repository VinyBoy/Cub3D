/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:37:09 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/04 18:46:59 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_exec(t_exec *exec)
{
	char	**map;

	map[0] = "1111111";
	map[1] = "1000001";
	map[2] = "1000001";
	map[3] = "1000001";
	map[4] = "1000001";
	map[5] = "1000001";
	map[5] = "1111111";
	map[6] = NULL;
	exec->map = map;
	//exec->map = init_map();
	exec->map_width = 7;
	exec->map_height = 7;
	exec->win_height = 760;
	exec->win_width = 1660;
	exec->player.x = 22.0;
	exec->player.y = 12.0;
	exec->player.dir_x = -1.0;
	exec->player.dir_y = 0.0;
	exec->player.plane_x = 0.0;  // fov horizonta;
	exec->player.plane_y = 0.66; // fov vertical
	exec->map ==
}

void	ft_exec(int argc, char **argv)
{
	t_exec	exec;

	(void)argc;
	(void)argv;
	init_exec(&exec);
	if (!init_mlx(&exec))
		return (free_exec_exit(&exec));
}

/*
	idees :

	etant donnee que l'image doit s'adapter a la map
		->creer une fonction qui va lire les lignes horizontales et verticale
			->ajuster win->height et win->height avant la mlx_loop

*/