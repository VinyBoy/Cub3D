/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:28:08 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/04 14:24:00 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*0 pour les espaces
vides, 1 pour les murs, et N,S,E ou W qui représentent la position de départ
du joueur et son orientation.*/

int	check_content(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '0' && map[i][j] != '0'
				&& map[i][j] != '0' && map[i][j] != '0' && map[i][j] != '0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

// int	check_map(char **map)
// {
// }

void	copy_with_single_spaces(char *line, char *c_line, int *i, int *j)
{
	while (line[*i])
	{
		if (line[*i] != ' ' && line[*i] != '\t')
			c_line[(*j)++] = line[*i];
		else if ((line[*i] == ' ' || line[*i] == '\t') && *j > 0
			&& c_line[*j - 1] != ' ')
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
	while (line[i] && (line[i] == ' ' || line[i] == 't'))
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

int	all_info_complete(t_assets *assets)
{
	if (assets->no_count == 1 && assets->so_count == 1 && assets->we_count == 1
		&& assets->ea_count == 1 && assets->f_count == 1
		&& assets->c_count == 1)
		return (1);
	return (0);
}

int	read_map(t_assets *assets)
{
	char	*line;
	char	*c_line;
	int		t_size;
	int		c_size;
	int		m_size;

	t_size = 0;
	c_size = 0;
	m_size = 0;
	line = get_next_line(assets->fd);
	while (line)
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
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
			assets->colors = line_to_array(assets->colors, c_line, &c_size);
			if (!assets->colors)
				return (free(line), 0);
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
			return (free(c_line), free(line),
				error("Error\nInvalid line in file\n"), 0);
		}
		free(c_line);
		free(line);
		line = get_next_line(assets->fd);
	}
	return (1);
}

void	print_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		printf("%s\n", array[i]);
}

t_assets	*parse_map(t_cub *cub, char **argv)
{
	t_assets	*assets;

	assets = malloc(sizeof(t_assets));
	if (!assets)
		return (error("Error\nMalloc error for assets\n"), NULL);
	ft_memset(assets, 0, sizeof(t_assets));
	(void)cub;
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
		if (!read_map(assets))
			return (close(assets->fd), free_assets(assets), NULL);
		if (!check_all_textures_present(assets))
			return (free_assets(assets), NULL);
		print_array(assets->textures);
		print_array(assets->colors);
		print_array(assets->map);
	}
	return (assets);
}
