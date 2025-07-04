/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:40:11 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/04 16:45:17 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_forward(t_exec *exec)
{
	exec->player.x += exec->player.dir_x * MOVE_SPEED;
	exec->player.y += exec->player.dir_y * MOVE_SPEED;
}

void	move_backward(t_exec *exec)
{
	exec->player.x += exec->player.dir_x * MOVE_SPEED;
	exec->player.y += exec->player.dir_x * MOVE_SPEED;
}

void	move_left(t_exec *exec)
{
	exec->player.x += exec->player.plane_x * MOVE_SPEED;
	exec->player.y += exec->player.plane_y * MOVE_SPEED;
}

void	move_right(t_exec *exec)
{
	exec->player.x += exec->player.plane_x * MOVE_SPEED;
	exec->player.y += exec->player.plane_y * MOVE_SPEED;
}
