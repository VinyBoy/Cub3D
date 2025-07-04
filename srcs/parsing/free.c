/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:35:35 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/04 11:25:55 by oztozdem         ###   ########.fr       */
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

void	free_assets(t_assets *assets)
{
	if (assets)
	{
		if (assets->textures)
			free_array(assets->textures);
		if (assets->colors)
			free_array(assets->colors);
		if (assets->map)
			free_array(assets->map);
		if (assets->fd >= 0)
			close(assets->fd);
		free(assets);
	}
}
