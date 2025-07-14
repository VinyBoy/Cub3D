/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:35:35 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/14 18:23:15 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	free_img(t_img *img)
{
	if (img)
	{
		if (img->north)
			free(img->north);
		if (img->south)
			free(img->south);
		if (img->east)
			free(img->east);
		if (img->west)
			free(img->west);
		free(img);
	}
}

void	free_assets(t_assets *assets)
{
	if (assets)
	{
		if (assets->textures)
			free_array(assets->textures);
		if (assets->map)
			free_array(assets->map);
		if (assets->fd >= 0)
			close(assets->fd);
		if (assets->img)
			free_img(assets->img);
		free(assets);
	}
}

void	free_visited(char **visited, int i)
{
	while (--i >= 0)
		free(visited[i]);
	free(visited);
}
