/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:37:24 by viny              #+#    #+#             */
/*   Updated: 2025/07/11 19:43:35 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	clear_image(t_exec *exec)
{
	mlx_destroy_image(exec->mlx, exec->image);
	exec->image = mlx_new_image(exec->mlx, exec->win_width, exec->win_height);
	exec->img_data = mlx_get_data_addr(exec->image, &exec->bpp,
			&exec->size_line, &exec->endian);
}

void	draw_floor_and_ceiling(t_exec *exec)
{
	int	x;
	int	y;

	y = -1;
	while (++y < exec->win_height / 2)
	{
		x = -1;
		while (++x < exec->win_width)
			put_pixel(exec, x, y, exec->ceiling_ex);
	}
	y = exec->win_height / 2;
	while (y < exec->win_height)
	{
		x = -1;
		while (++x < exec->win_width)
			put_pixel(exec, x, y, exec->floor_ex);
		y++;
	}
}
int	render_frame(t_exec *exec)
{
	int	x;

	clear_image(exec);
	draw_floor_and_ceiling(exec);
	x = 0;
	while (x < exec->win_width)
	{
		cast_ray(exec, x);
		x++;
	}
	mlx_put_image_to_window(exec->mlx, exec->win, exec->image, 0, 0);
	return (0);
}

void	cast_ray(t_exec *exec, int x)
{
	t_ray	r;

	init_ray(exec, &r, x);
	perform_dda(exec, &r);
	compute_wall(exec, &r);
	draw_column(exec, x, &r);
}

void	compute_wall(t_exec *exec, t_ray *r)
{
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - exec->player.x + (1 - r->step_x) / 2)
			/ r->ray_dir_x;
	else
		r->perp_wall_dist = (r->map_y - exec->player.y + (1 - r->step_y) / 2)
			/ r->ray_dir_y;
	r->line_height = (int)(exec->win_height / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + exec->win_height / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + exec->win_height / 2;
	if (r->draw_end >= exec->win_height)
		r->draw_end = exec->win_height - 1;
}

void	draw_column(t_exec *exec, int x, t_ray *r)
{
	int	y;
	int	color;

	color = (r->side == 1) ? 0x00777777 : 0x00BBBBBB;
	y = r->draw_start;
	while (y < r->draw_end)
	{
		put_pixel(exec, x, y, color);
		y++;
	}
}
