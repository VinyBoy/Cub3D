/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:43:59 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/14 13:13:47 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// int	handle_textures(t_assets *assets, char *c_line)
// {
// 	if (assets->map_started)
// 		return (error("Error\nTexture found after map start\n"), 0);
// 	if (!check_texture_duplicates(assets, c_line))
// 		return (error("Error\nDuplicate texture found\n"), 0);
// 	assets->textures = line_to_array(assets->textures, c_line, &assets->t_size);
// 	if (!assets->textures)
// 		return (0);
// 	return (1);
// }

// int	handle_colors(t_assets *assets, char *c_line)
// {
// 	if (assets->map_started)
// 		return (error("Error\nColor found after map start\n"), 0);
// 	if (!check_color_duplicates(assets, c_line))
// 		return (error("Error\nDuplicate color found\n"), 0);
// 	if (!store_color(assets, c_line))
// 		return (error("Error\nInvalid color format\n"), 0);
// 	return (1);
// }

// int	handle_map(t_assets *assets, char *line)
// {
// 	if (!all_info_complete(assets))
// 		return (error("Error\nMap found before all assets defined\n"), 0);
// 	assets->map_started = 1;
// 	assets->map = line_to_array(assets->map, line, &assets->m_size);
// 	if (!assets->map)
// 		return (0);
// 	return (1);
// }

// int	process_line(t_assets *assets, char *line)
// {
// 	char	*c_line;

// 	c_line = clean_line(line);
// 	if (!c_line)
// 		return (0);
// 	if (is_texture(c_line))
// 	{
// 		if (!handle_textures(assets, line))
// 			return (free(c_line), 0);
// 	}
// 	else if (is_color(c_line))
// 	{
// 		if (!handle_colors(assets, line))
// 			return (free(c_line), 0);
// 	}
// 	else if (is_map(line))
// 	{
// 		if (!handle_map(assets, line))
// 			return (free(c_line), 0);
// 	}
// 	else
// 	{
// 		if (assets->map_started)
// 			return (free(c_line), 2);
// 		return (free(c_line), error("Error\nInvalid line in file\n"), 0);
// 	}
// 	free(c_line);
// 	return (1);
// }

// int	check_empty_lines_in_map(t_assets *assets)
// {
// 	char	*next_line;

// 	next_line = get_next_line(assets->fd);
// 	while (next_line)
// 	{
// 		if (next_line[0] != '\n' && next_line[0] != '\0')
// 			if (is_map(next_line))
// 				return (free(next_line), error("Error\nEmpty line in map\n"),
// 					0);
// 		free(next_line);
// 		next_line = get_next_line(assets->fd);
// 	}
// 	return (1);
// }

// int	read_map(t_assets *assets)
// {
// 	char	*line;
// 	int		result;

// 	line = get_next_line(assets->fd);
// 	while (line)
// 	{
// 		if (line[0] == '\n' || line[0] == '\0')
// 		{
// 			if (assets->map_started)
// 			{
// 				if (!check_empty_lines_in_map(assets))
// 					return (free(line), 0);
// 				free(line);
// 				break ;
// 			}
// 			free(line);
// 			line = get_next_line(assets->fd);
// 			continue ;
// 		}
// 		result = process_line(assets, line);
// 		if (result == 0)
// 			return (free(line), 0);
// 		if (result == 2)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		free(line);
// 		line = get_next_line(assets->fd);
// 	}
// 	return (1);
// }

#include "../../include/cub3d.h"

int	process_line(t_assets *assets, char *line)
{
	char	*c_line;
	int		result;

	result = 1;
	c_line = clean_line(line);
	if (!c_line)
		return (0);
	if (is_texture(c_line))
		result = handle_textures(assets, c_line);
	else if (is_color(c_line))
		result = handle_colors(assets, c_line);
	else if (is_map(line))
		result = handle_map(assets, line);
	else if (assets->map_started)
		result = 2;
	else
		result = (error("Error\nInvalid line in file\n"), 0);
	free(c_line);
	return (result);
}

int	process_current_line(t_assets *assets, char *line)
{
	int	result;

	if (line[0] == '\n' || line[0] == '\0')
		return (handle_empty_line(assets));
	result = process_line(assets, line);
	return (result);
}

int	read_map(t_assets *assets)
{
	char	*line;
	int		result;

	line = get_next_line(assets->fd);
	while (line)
	{
		result = process_current_line(assets, line);
		free(line);
		if (result == 0)
			return (0);
		if (result == 2)
			break ;
		line = get_next_line(assets->fd);
	}
	return (1);
}
