/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:37:09 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/04 16:33:35 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_exec(t_exec *exec)
{
	exec->win_height = 760;
	exec->win_width = 1660;
	exec->player.x = 22.0;
	exec->player.y = 12.0;
	exec->player.dir_x = -1.0;
	exec->player.dir_y = 0.0;
	exec->player.plane_x = 0.0; // fov horizonta;
	exec->player.plane_y = 0.66; // fov vertical
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