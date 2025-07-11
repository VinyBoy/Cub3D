/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:12:08 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/11 15:05:52 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_cub	*init_cub(char **argv)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (error("Error\nMalloc error on t_cub struct\n"), NULL);
	ft_memset(cub, 0, sizeof(t_cub));
	cub->assets = parse_map(argv);
	if (!cub->assets)
		return (free_all(cub), NULL);
	return (cub);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc != 2)
		return (error("Error\nUsage: ./cub3D <map.cub>\n"), 1);
	cub = init_cub(argv);
	if (!cub)
		return (free_all(cub), 1);
	free_all(cub);
	return (0);
}
