/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:16:48 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/15 14:32:40 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	handle_window_close(t_exec *exec)
{
	free_exec_exit(exec);
	return (0);
}

int	init_mlx(t_exec *exec)
{
	exec->mlx = mlx_init();
	if (!exec->mlx)
		return (0);
	exec->win = mlx_new_window(exec->mlx, exec->win_width, exec->win_height,
			"cub3D");
	if (!exec->win)
		return (0);
	if (!set_img(exec))
		return (0);
	// mlx_key_hook(exec->win, key_hook, exec);
	mlx_hook(exec->win, 2, 1L << 0, key_hook, exec);
	mlx_hook(exec->win, 17, 0, handle_window_close, exec);
	exec->image = mlx_new_image(exec->mlx, exec->win_width, exec->win_height);
	exec->img_data = mlx_get_data_addr(exec->image, &exec->bpp,
			&exec->size_line, &exec->endian);
	mlx_put_image_to_window(exec->mlx, exec->win, exec->image, 0, 0);
	mlx_loop_hook(exec->mlx, render_frame, exec);
	mlx_loop(exec->mlx);
	return (1);
}
