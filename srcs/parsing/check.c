/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:46:02 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/04 16:38:28 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

int	all_info_complete(t_assets *assets)
{
	if (assets->no_count == 1 && assets->so_count == 1 && assets->we_count == 1
		&& assets->ea_count == 1 && assets->f_count == 1
		&& assets->c_count == 1)
		return (1);
	return (0);
}

int	check_map(char **map)
{
	int	i;
	int	j;
	int	count_p;

	i = -1;
	count_p = 0;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'
				&& map[i][j] != ' ')
				return (error("Error\nInvalid character\n"), 0);
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				count_p++;
			j++;
		}
	}
	if (count_p != 1)
		return (error("Error\nWrong amount of player\n"), 0);
	return (1);
}
