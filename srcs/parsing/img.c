/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:15:55 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/14 20:47:11 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*get_texture_path(char **textures, char *id)
{
	int		i;
	char	*start;

	i = 0;
	while (textures[i])
	{
		if (!ft_strncmp(textures[i], id, 3))
		{
			start = ft_strdup(textures[i] + 3);
			if (!start)
				return (NULL);
			return (start);
		}
		i++;
	}
	return (NULL);
}

int	set_path(t_assets *assets)
{
	assets->img->north = get_texture_path(assets->textures, "NO ");
	if (!assets->img->north)
		return (error("Error\nImage path setting failed\n"), 0);
	assets->img->south = get_texture_path(assets->textures, "SO ");
	if (!assets->img->south)
		return (error("Error\nImage path setting failed\n"), 0);
	assets->img->east = get_texture_path(assets->textures, "EA ");
	if (!assets->img->east)
		return (error("Error\nImage path setting failed\n"), 0);
	assets->img->west = get_texture_path(assets->textures, "WE ");
	if (!assets->img->west)
		return (error("Error\nImage path setting failed\n"), 0);
	assets->img->height = 128;
	assets->img->width = 128;
	return (1);
}

int	set_img(t_assets *assets)
{
	assets->img = malloc(sizeof(t_img));
	if (!assets->img)
		return (error("Error\nMalloc error struct img\n"), 0);
	ft_memset(assets->img, 0, sizeof(t_img));
	if (!set_path(assets))
		return (0);
	return (1);
}
