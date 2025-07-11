/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viny <viny@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:36:59 by viny              #+#    #+#             */
/*   Updated: 2025/07/10 16:49:29 by viny             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_ray(t_exec *exec, t_ray *r, int x)
{
	r->camera_x = 2 * x / (double)exec->win_width - 1;
	r->ray_dir_x = exec->player.dir_x
		+ exec->player.plane_x * r->camera_x;
	r->ray_dir_y = exec->player.dir_y
		+ exec->player.plane_y * r->camera_x;
	r->map_x = (int)exec->player.x;
	r->map_y = (int)exec->player.y;
	r->delta_dist_x = fabs(1 / r->ray_dir_x);
	r->delta_dist_y = fabs(1 / r->ray_dir_y);
	init_steps(exec, r);
}

void	init_steps(t_exec *exec, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (exec->player.x - r->map_x)
			* r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - exec->player.x)
			* r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (exec->player.y - r->map_y)
			* r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - exec->player.y)
			* r->delta_dist_y;
	}
}

void	perform_dda(t_exec *exec, t_ray *r)
{
	r->hit = 0;
	while (!r->hit)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (exec->map[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}
