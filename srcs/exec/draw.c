/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:16:18 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/04 16:26:45 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
