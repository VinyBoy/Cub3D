/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:12:08 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/07 12:10:10 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc != 2)
		return (error("Error\nUsage: ./cub3D <map.cub>\n"), 1);
	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (error("Error\nMalloc error on t_cub struct\n"), 1);
	ft_memset(cub, 0, sizeof(t_cub));
	cub->assets = parse_map(cub, argv);
	free_assets(cub->assets);
	free(cub);
	return (0);
}
