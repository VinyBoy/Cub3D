/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:17:23 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/04 16:17:47 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_exec_exit(t_exec *exec)
{
	if (exec->mlx != NULL)
	{
		mlx_destroy_image(exec->mlx, exec->image);
		mlx_destroy_window(exec->mlx, exec->win);
		mlx_destroy_display(exec->win);
		free(exec->mlx);
	}
	free(exec);
	exit(1);
}
