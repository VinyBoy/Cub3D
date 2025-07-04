/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:40:25 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/04 16:50:00 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	rotate_left(t_exec *exec)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = exec->player.dir_x;
	old_plane_x = exec->player.plane_x;
	exec->player
}