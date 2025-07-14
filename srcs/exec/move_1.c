/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:40:11 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/11 17:51:41 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_forward(t_exec *exec)
{
	double	new_x;
	double	new_y;

	new_x = exec->player.x + exec->player.dir_x * MOVE_SPEED;
	new_y = exec->player.y + exec->player.dir_y * MOVE_SPEED;
	// Collision sur X (on garde l'ancien Y)
	if (exec->map[(int)exec->player.y][(int)new_x] != '1'
		&& exec->map[(int)exec->player.y][(int)new_x] != 'X')
		exec->player.x = new_x;
	// Collision sur Y (on garde l'ancien X)
	if (exec->map[(int)new_y][(int)exec->player.x] != '1'
		&& exec->map[(int)new_y][(int)exec->player.x] != 'X')
		exec->player.y = new_y;
}

void	move_backward(t_exec *exec)
{
	double	new_x;
	double	new_y;

	new_x = exec->player.x - exec->player.dir_x * MOVE_SPEED;
	new_y = exec->player.y - exec->player.dir_y * MOVE_SPEED;
	if (exec->map[(int)exec->player.y][(int)new_x] != '1'
		&& exec->map[(int)exec->player.y][(int)new_x] != 'X')
		exec->player.x = new_x;
	if (exec->map[(int)new_y][(int)exec->player.x] != '1'
		&& exec->map[(int)new_y][(int)exec->player.x] != 'X')
		exec->player.y = new_y;
}

void	move_left(t_exec *exec)
{
	double	new_x;
	double	new_y;

	new_x = exec->player.x - exec->player.plane_x * MOVE_SPEED;
	new_y = exec->player.y - exec->player.plane_y * MOVE_SPEED;
	if (exec->map[(int)exec->player.y][(int)new_x] != '1'
		&& exec->map[(int)exec->player.y][(int)new_x] != 'X')
		exec->player.x = new_x;
	if (exec->map[(int)new_y][(int)exec->player.x] != '1'
		&& exec->map[(int)new_y][(int)exec->player.x] != 'X')
		exec->player.y = new_y;
}

void	move_right(t_exec *exec)
{
	double	new_x;
	double	new_y;

	new_x = exec->player.x + exec->player.plane_x * MOVE_SPEED;
	new_y = exec->player.y + exec->player.plane_y * MOVE_SPEED;
	if (exec->map[(int)exec->player.y][(int)new_x] != '1'
		&& exec->map[(int)exec->player.y][(int)new_x] != 'X')
		exec->player.x = new_x;
	if (exec->map[(int)new_y][(int)exec->player.x] != '1'
		&& exec->map[(int)new_y][(int)exec->player.x] != 'X')
		exec->player.y = new_y;
}
