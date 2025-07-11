/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:37:09 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/11 16:09:58 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_exec(t_exec *exec, t_cub *cub)
{
	(void)cub;
	static char *tmp_map[] = {
		"1111111111111111111111111",
		"1000000000110000000000001",
		"1011000001110000000000001",
		"1001000000000000000000001",
		"11111111101100000111000001",
		"1000000000110000011101111",
		"11110111111111011100000010001",
		"11110111111111011101010010001",
		"11000000110101011100000010001",
		"10000000000000001100000010001",
		"10000000000000001101010010001",
		"11000001110101011111011110N0111",
		"11110111011101010101111010001",
		"1111111101111111011111111111",
		NULL
	};
	exec->map = tmp_map;
	exec->map_width = 30;
	exec->map_height = 14;
	exec->win_height = 800;
	exec->win_width = 1400;
	exec->player.x = 11.5;
	exec->player.y = 11.5;
	exec->player.dir_x = -1.0;
	exec->player.dir_y = 0.0;
	exec->player.plane_x = 0.0;  // fov horizonta;
	exec->player.plane_y = 0.66; // fov vertical
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