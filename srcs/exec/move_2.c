/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:40:25 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/11 13:22:50 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// void	rotate_left(t_exec *exec)
// {
// 	double	old_dir_x;
// 	double	old_plane_x;

// 	old_dir_x = exec->player.dir_x;
// 	old_plane_x = exec->player.plane_x;
// 	exec->player.dir_x = exec->player.dir_x * cos(-ROT_SPEED)
// 		- exec->player.dir_y * sin(-ROT_SPEED);
// 	exec->player.dir_y = old_dir_x * sin(-ROT_SPEED) + exec->player.dir_y
// 		* cos(-ROT_SPEED);
// 	exec->player.plane_x = exec->player.plane_x * cos(-ROT_SPEED)
// 		- exec->player.plane_y * sin(-ROT_SPEED);
// 	exec->player.plane_y = old_plane_x * sin(-ROT_SPEED) - exec->player.plane_y
// 		* cos(-ROT_SPEED);
// }

// void	rotate_right(t_exec *exec)
// {
// 	double	old_dir_x;
// 	double	old_plane_x;

// 	old_dir_x = exec->player.dir_x;
// 	old_plane_x = exec->player.plane_x;
// 	exec->player.dir_x = exec->player.dir_x * cos(ROT_SPEED)
// 		- exec->player.dir_y * sin(ROT_SPEED);
// 	exec->player.dir_y = old_dir_x * sin(ROT_SPEED) + exec->player.dir_y
// 		* cos(ROT_SPEED);
// 	exec->player.plane_x = exec->player.plane_x * cos(ROT_SPEED)
// 		- exec->player.plane_y * sin(ROT_SPEED);
// 	exec->player.plane_y = old_plane_x * sin(ROT_SPEED) - exec->player.plane_y
// 		* cos(ROT_SPEED);
// }

void	rotate(t_exec *exec, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = exec->player.dir_x;
	exec->player.dir_x = exec->player.dir_x * cos(angle) - exec->player.dir_y
		* sin(angle);
	exec->player.dir_y = old_dir_x * sin(angle) + exec->player.dir_y
		* cos(angle);
	old_plane_x = exec->player.plane_x;
	exec->player.plane_x = exec->player.plane_x * cos(angle)
		- exec->player.plane_y * sin(angle);
	exec->player.plane_y = old_plane_x * sin(angle) + exec->player.plane_y
		* cos(angle);
}
