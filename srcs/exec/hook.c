/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:17:59 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/04 16:39:23 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	mouse_hook(int mouse_code, t_exec *exec)
{
	if (mouse_code == ON_DESTROY)
		return (free_exec_exit(exec), 0);
	return (1);
}

int	key_hook(int keysym, t_exec *exec)
{
	if (keysym == XK_Escape)
		return (free_exec_exit(exec), 0);
	if (keysym == XK_w || keysym == XK_W)
		move_forward(exec);
	else if (keysym == XK_s || keysym == XK_S)
		move_backward(exec);
	else if (keysym == XK_a || keysym == XK_A)
		move_left(exec);
	else if (keysym == XK_d || keysym == XK_D)
		move_right(exec);
	else if (keysym == XK_Left)
		rotate_left(exec);
	else if (keysym == XK_Right)
		rotate_right(exec);
	return (1);
}

