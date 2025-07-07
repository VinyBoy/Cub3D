/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:47:28 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/07 11:54:23 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	wall_or_void(char c)
{
	return (c == '1' || c == ' ' || c == '\t');
}

int	check_left_right_borders(char **map, int map_height)
{
	int	line_len;
	int	i;

	i = -1;
	while (++i < map_height)
	{
		line_len = ft_strlen(map[i]);
		if (line_len > 0)
		{
			if (!wall_or_void(map[i][0]))
				return (error("Error\nMap not closed (left border)\n"), 0);
			if (!wall_or_void(map[i][line_len - 1]))
				return (error("Error\nMap not closed (right border)\n"), 0);
		}
	}
	return (1);
}

int	check_borders(char **map)
{
	int	i;
	int	map_height;

	i = 0;
	while (map[i])
		i++;
	map_height = i;
	i = -1;
	while (map[0][++i])
		if (!wall_or_void(map[0][i]))
			return (error("Error\nMap not closed\n"), 0);
	i = -1;
	while (map[map_height - 1][++i])
		if (!wall_or_void(map[map_height - 1][i]))
			return (error("Error\nMap not closed\n"), 0);
	if (!check_left_right_borders(map, map_height))
		return (0);
	return (1);
}

int	check_enclosed(char **map, int x, int y)
{
	int	map_height;
	int	line_len;

	if (!map || !map[y])
		return (0);
	map_height = 0;
	while (map[map_height])
		map_height++;
	line_len = ft_strlen(map[y]);
	if (y == 0 || y == map_height - 1 || x == 0 || x >= line_len - 1)
		return (0);
	if (y > 0 && x >= (int)ft_strlen(map[y - 1]))
		return (0);
	if (y < map_height - 1 && x >= (int)ft_strlen(map[y + 1]))
		return (0);
	return (1);
}

int	check_map_enclosed(char **map)
{
	int	i;
	int	j;

	if (!check_borders(map))
		return (0);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (!check_enclosed(map, j, i))
					return (error("Error\nMap not properly enclosed\n"), 0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
