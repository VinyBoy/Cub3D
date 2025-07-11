/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:28:08 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/11 17:23:46 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*0 pour les espaces
vides, 1 pour les murs, et N,S,E ou W qui représentent la position de départ
du joueur et son orientation.*/

void	copy_with_single_spaces(char *line, char *c_line, int *i, int *j)
{
	while (line[*i])
	{
		if (line[*i] != ' ')
			c_line[(*j)++] = line[*i];
		else if (line[*i] == ' ' && *j > 0 && c_line[*j - 1] != ' ')
			c_line[(*j)++] = ' ';
		(*i)++;
	}
}

char	*clean_line(char *line)
{
	char	*c_line;
	int		i;
	int		j;

	i = ft_strlen(line);
	if (i > 0 && line[i - 1] == '\n')
		line[i - 1] = '\0';
	c_line = malloc(sizeof(char) * (i + 1));
	if (!c_line)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] && line[i] == ' ')
		i++;
	copy_with_single_spaces(line, c_line, &i, &j);
	if (j > 0 && c_line[j - 1] == ' ')
		j--;
	c_line[j] = '\0';
	return (c_line);
}

char	**line_to_array(char **array, char *line, int *size)
{
	char	**new_array;
	int		i;

	new_array = malloc(sizeof(char *) * (*size + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	if (array)
	{
		while (i < *size)
		{
			new_array[i] = array[i];
			i++;
		}
		free(array);
	}
	new_array[i] = ft_strdup(line);
	new_array[i + 1] = NULL;
	(*size)++;
	return (new_array);
}

int	read_map(t_assets *assets)
{
	char	*line;
	char	*c_line;
	int		t_size;
	int		c_size;
	int		m_size;
	char	*next_line;

	t_size = 0;
	c_size = 0;
	m_size = 0;
	line = get_next_line(assets->fd);
	while (line)
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			if (assets->map_started)
			{
				while ((next_line = get_next_line(assets->fd)))
				{
					if (next_line[0] != '\n' && next_line[0] != '\0')
					{
						if (is_map(next_line))
						{
							free(next_line);
							return (free(line),
								error("Error\nEmpty line in map\n"), 0);
						}
					}
					free(next_line);
				}
				free(line);
				break ;
			}
			free(line);
			line = get_next_line(assets->fd);
			continue ;
		}
		c_line = clean_line(line);
		if (!c_line)
			return (free(line), 0);
		if (is_texture(c_line))
		{
			if (assets->map_started)
				return (free(c_line), free(line),
					error("Error\nTexture found after map start\n"), 0);
			if (!check_texture_duplicates(assets, c_line))
				return (free(c_line), free(line),
					error("Error\nDuplicate texture found\n"), 0);
			assets->textures = line_to_array(assets->textures, c_line, &t_size);
			if (!assets->textures)
				return (free(line), 0);
		}
		else if (is_color(c_line))
		{
			if (assets->map_started)
				return (free(c_line), free(line),
					error("Error\nColor found after map start\n"), 0);
			if (!check_color_duplicates(assets, c_line))
				return (free(c_line), free(line),
					error("Error\nDuplicate color found\n"), 0);
			if (!store_color(assets, c_line))
				return (free(c_line), free(line),
					error("Error\nInvalid color format\n"), 0);
		}
		else if (is_map(line))
		{
			if (!all_info_complete(assets))
				return (free(c_line), free(line),
					error("Error\nMap found before all assets defined\n"), 0);
			assets->map_started = 1;
			assets->map = line_to_array(assets->map, line, &m_size);
			if (!assets->map)
				return (free(line), 0);
		}
		else
		{
			if (assets->map_started)
			{
				free(c_line);
				free(line);
				break ;
			}
			return (free(c_line), free(line),
				error("Error\nInvalid line in file\n"), 0);
		}
		free(c_line);
		free(line);
		line = get_next_line(assets->fd);
	}
	return (1);
}

int	parsing(t_assets *assets)
{
	char	**filled_map;

	if (!read_map(assets))
		return (free_assets(assets), 0);
	if (!check_all_textures_present(assets))
		return (free_assets(assets), 0);
	if (!assets->map)
		return (free_assets(assets), error("Error\nNo map found\n"), 0);
	if (!check_map(assets->map))
		return (free_assets(assets),
			error("Error\nUnvalid caracter detected\n"), 0);
	if (!check_borders(assets->map))
		return (free_assets(assets), 0);
	filled_map = fill_map(assets->map);
	if (!filled_map)
		return (free_assets(assets), 0);
	free_array(assets->map);
	assets->map = filled_map;
	if (!check_closed(assets->map))
		return (free_assets(assets), 0);
	if (!check_textures(assets->textures))
		return (free_assets(assets), 0);
	return (1);
}

int	is_directory(const char *path)
{
	int		fd;
	char	buffer[1];
	ssize_t	r;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error("Error\nOpen failed\n"), 0);
	r = read(fd, buffer, 1);
	close(fd);
	if (r == -1)
		return (error("Error\nInvalid map file type\n"), 1);
	return (0);
}

t_assets	*parse_map(char **argv)
{
	t_assets	*assets;

	assets = init_assets();
	if (!assets)
		return (error("Error\nAssets init failed\n"), NULL);
	// if (is_directory(argv[1]))
	// 	return (0);
	if (ft_strrchr(argv[1], '/'))
	{
		if (ft_strlen(ft_strrchr(argv[1], '/') + 1) < 5)
			return (error("Error\nMap is wrong\n"), NULL);
	}
	if (c_strchr(argv[1], ".cub") == 0)
		return (error("Error\nMap must be a .cub\n"), NULL);
	else
	{
		assets->fd = open(argv[1], O_RDONLY);
		if (assets->fd <= 0)
			return (free(assets), error("Error\nCannot open file\n"), NULL);
		if (!parsing(assets))
			return (NULL);
	}
	print_assets(assets);
	return (assets);
}
