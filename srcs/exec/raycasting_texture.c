/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:13:19 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/16 15:46:17 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_texture_mlx	*get_wall_texture(t_exec *exec, t_ray *r)
{
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0)
			return (exec->assets->east);
		else
			return (exec->assets->west);
	}
	else
	{
		if (r->ray_dir_y > 0)
			return (exec->assets->south);
		else
			return (exec->assets->north);
	}
}

int	get_wall_x(t_exec *exec, t_ray *r)
{
	double	wall_x;

	if (r->side == 0)
		wall_x = exec->player.y + r->perp_wall_dist * r->ray_dir_y;
	else
		wall_x = exec->player.x + r->perp_wall_dist * r->ray_dir_x;
	wall_x -= floor(wall_x);
	return ((int)(wall_x * (double)exec->assets->north->win_width));
}

int	get_tex_x(t_exec *exec, t_texture_mlx *texture, t_ray *r)
{
	int	tex_x;

	tex_x = get_wall_x(exec, r);
	if (r->side == 0 && r->ray_dir_x > 0)
		tex_x = texture->win_width - tex_x - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		tex_x = texture->win_width - tex_x - 1;
	return (tex_x);
}

void	draw_wall_line(t_exec *exec, t_texture_mlx *texture, int x,
		t_tex_info *tex, t_ray *r)
{
	int	tex_y;
	int	color;

	while (tex->y < tex->end)
	{
		tex_y = (int)tex->tex_pos & (texture->win_height - 1);
		tex->tex_pos += tex->step;
		color = *(int *)(texture->img_data + (tex_y * texture->size_line
					+ tex->tex_x * (texture->bpp / 8)));
		if (r->side == 1)
			color = (color >> 1) & 8355711;
		put_pixel(exec, x, tex->y, color);
		tex->y++;
	}
}

void	draw_textured_wall(t_exec *exec, int x, t_tex_info *tex_info, t_ray *r)
{
	t_texture_mlx	*texture;

	texture = get_wall_texture(exec, r);
	if (!texture || !texture->img_data)
		return ;
	tex_info->tex_x = get_tex_x(exec, texture, r);
	tex_info->step = 1.0 * texture->win_height / tex_info->line_height;
	tex_info->tex_pos = (tex_info->y - exec->win_height / 2
			+ tex_info->line_height / 2) * tex_info->step;
	draw_wall_line(exec, texture, x, tex_info, r);
}

void	draw_column(t_exec *exec, int x, t_ray *r)
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_tex_info	tex_info;

	line_height = (int)(exec->win_height / r->perp_wall_dist);
	draw_start = -line_height / 2 + exec->win_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + exec->win_height / 2;
	if (draw_end >= exec->win_height)
		draw_end = exec->win_height - 1;
	tex_info.line_height = line_height;
	tex_info.y = draw_start;
	tex_info.end = draw_end;
	draw_textured_wall(exec, x, &tex_info, r);
}
