/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:16:18 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/04 18:08:52 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	render_frame(t_exec *exec)
{
	int	px;
	int	py;

	px = (int)(exec->player.x * 10);
	py = (int)(exec->player.y * 10);
	// Efface l'image
	mlx_destroy_image(exec->mlx, exec->image);
	exec->image = mlx_new_image(exec->mlx, exec->win_width, exec->win_height);
	exec->img_data = mlx_get_data_addr(exec->image, &exec->bpp,
			&exec->size_line, &exec->endian);
	// Dessine le joeur
	draw_something(exec, px - 5, py - 5, 10);
	// dessine la direction
	draw_direction(exec, px, py, exec->player.dir_x, exec->player.dir_y);
	mlx_put_image_to_window(exec->mlx, exec->win, exec->image, 0, 0);
	return (1);
}

void	draw_direction(t_exec *exec, int x, int y, double dx, double dy)
{
	int	i;
	int	lenght;
	int	px;
	int	py;

	i = 0;
	// counte la ligne on recupera avec le parsing
	lenght = 20;
	while (i < lenght)
	{
		px = x + dx * i;
		py = y + dy * i;
		put_pixel(exec, px, py, 0x00FFFFFF);
		i++;
	}
}

void	draw_something(t_exec *exec, int x_start, int y_start, int size)
{
	int	x;
	int	y;

	y = y_start;
	while (y < y_start + size)
	{
		x = x_start;
		while (x < x_start + size)
		{
			put_pixel(exec, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}
}

void	put_pixel(t_exec *exec, int x, int y, int color)
{
	char	*dst;

	dst = exec->img_data + (y * exec->size_line + x * (exec->bpp / 8));
	*(unsigned int *)dst = color;
}

void	create_image(t_exec *exec)
{
	int	center_x;
	int	center_y;

	center_x = exec->win_width / 2 - 200;
	center_y = exec->win_height / 2 - 200;
	draw_something(exec, center_x, center_y, 400);
}
