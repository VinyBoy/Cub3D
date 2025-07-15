/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:27:12 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/15 15:58:34 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_minimap_size(t_exec *exec)
{
	int	needed_width;
	int	needed_height;
	int	needed_size;
	int	max_screen_size;

	needed_width = exec->assets->map_width * MINIMAP_SCALE;
	needed_height = exec->assets->map_height * MINIMAP_SCALE;
	if (needed_width > needed_height)
		needed_size = needed_width;
	else
		needed_size = needed_height;
	max_screen_size = exec->win_width * 0.25;
	if (needed_size < MINIMAP_MIN_SIZE)
		return (MINIMAP_MIN_SIZE);
	if (needed_size > MINIMAP_MAX_SIZE || needed_size > max_screen_size)
	{
		if (MINIMAP_MAX_SIZE < max_screen_size)
			return (MINIMAP_MAX_SIZE);
		else
			return (max_screen_size);
	}
	return (needed_size);
}

void	draw_minimap_pixel(t_exec *exec, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			if (x + i < exec->win_width && y + j < exec->win_height)
				put_pixel(exec, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_border(t_exec *exec)
{
    int	i;
    int	border_color;
    int	minimap_size;

    minimap_size = get_minimap_size(exec);
    border_color = 0x00FFFFFF;
    i = 0;
    while (i < minimap_size + 4)
    {
        put_pixel(exec, MINIMAP_X - 2 + i, MINIMAP_Y - 2, border_color);
        put_pixel(exec, MINIMAP_X - 2 + i, MINIMAP_Y + minimap_size + 1, border_color);
        i++;
    }
    i = 0;
    while (i < minimap_size + 4)
    {
        put_pixel(exec, MINIMAP_X - 2, MINIMAP_Y - 2 + i, border_color);
        put_pixel(exec, MINIMAP_X + minimap_size + 1, MINIMAP_Y - 2 + i, border_color);
        i++;
    }
}

void	draw_minimap_background(t_exec *exec)
{
    int	x;
    int	y;
    int	bg_color;
    int	minimap_size;

    minimap_size = get_minimap_size(exec);
    y = 0;
    bg_color = 0x00333333;
    while (y < minimap_size)
    {
        x = 0;
        while (x < minimap_size)
        {
            put_pixel(exec, MINIMAP_X + x, MINIMAP_Y + y, bg_color);
            x++;
        }
        y++;
    }
}

void	draw_player_on_minimap(t_exec *exec)
{
    int	player_x;
    int	player_y;
    int	player_color;
    int	i;
    int	j;
    int	minimap_size;

    minimap_size = get_minimap_size(exec);
    i = -2;
    player_x = MINIMAP_X + (exec->player.x * MINIMAP_SCALE);
    player_y = MINIMAP_Y + (exec->player.y * MINIMAP_SCALE);
    player_color = 0x00FF0000;
    while (i <= 2)
    {
        j = -2;
        while (j <= 2)
        {
            if (player_x + i >= MINIMAP_X && player_x + i < MINIMAP_X + minimap_size 
                && player_y + j >= MINIMAP_Y && player_y + j < MINIMAP_Y + minimap_size)
                put_pixel(exec, player_x + i, player_y + j, player_color);
            j++;
        }
        i++;
    }
}

void	draw_minimap_map(t_exec *exec)
{
    int	map_x;
    int	map_y;
    int	wall_color;
    int	floor_color;
    int	minimap_size;

    minimap_size = get_minimap_size(exec);
    wall_color = 0x00FFFFFF;
    floor_color = 0x00000000;
    map_y = 0;
    while (map_y < exec->assets->map_height && map_y * MINIMAP_SCALE < minimap_size)
    {
        map_x = 0;
        while (exec->map[map_y][map_x] && map_x * MINIMAP_SCALE < minimap_size)
        {
            if (exec->map[map_y][map_x] == '1' || exec->map[map_y][map_x] == 'X')
                draw_minimap_pixel(exec, MINIMAP_X + map_x * MINIMAP_SCALE, 
                    MINIMAP_Y + map_y * MINIMAP_SCALE, wall_color);
            else if (exec->map[map_y][map_x] == '0' || is_player_char(exec->map[map_y][map_x])
                || exec->map[map_y][map_x] == 'V')
                draw_minimap_pixel(exec, MINIMAP_X + map_x * MINIMAP_SCALE, 
                    MINIMAP_Y + map_y * MINIMAP_SCALE, floor_color);
            map_x++;
        }
        map_y++;
    }
}

void	draw_minimap(t_exec *exec)
{
	if (!exec->show_minimap)
		return ;
	draw_minimap_background(exec);
	draw_minimap_border(exec);
	draw_minimap_map(exec);
	draw_player_on_minimap(exec);
}
