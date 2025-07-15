/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:13:19 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/07/15 16:02:03 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// static void	init_texinfo(t_exec *exec, t_ray *r, t_tex_info *tex)
// {
// 	tex->img = choose_texture_img(exec, r);
// 	tex->img_data = mlx_get_data_addr(tex->img, &exec->bpp, &exec->size_line,
// 			&exec->endian);
// 	// Récupère la taille de la bonne texture, pas une globale !
// 	if (r->side == 0 && r->ray_dir_x > 0)
// 	{
// 		tex->width = exec->assets->west->win_width;
// 		tex->height = exec->assets->west->win_height;
// 	}
// 	else if (r->side == 0 && r->ray_dir_x <= 0)
// 	{
// 		tex->width = exec->assets->east->win_width;
// 		tex->height = exec->assets->east->win_height;
// 	}
// 	else if (r->side == 1 && r->ray_dir_y > 0)
// 	{
// 		tex->width = exec->assets->north->win_width;
// 		tex->height = exec->assets->north->win_height;
// 	}
// 	else
// 	{
// 		tex->width = exec->assets->south->win_width;
// 		tex->height = exec->assets->south->win_height;
// 	}
// 	tex->y = 0;
// 	printf("Texture size: %d x %d\n", tex->width, tex->height);
// }

// void	draw_column(t_exec *exec, int x, t_ray *r)
// {
// 	t_tex_info	tex_info;

// 	init_texinfo(exec, r, &tex_info);
// 	draw_texture_column(exec, x, r, &tex_info);
// }

void	draw_column(t_exec *exec, int x, t_ray *r)
{
	int	y;
	int	color;

	if (r->side == 1)
		color = 0x00777777;
	else
		color = 0x00BBBBBB;
	y = r->draw_start;
	while (y < r->draw_end)
	{
		put_pixel(exec, x, y, color);
		y++;
	}
}

void	draw_texture_column(t_exec *exec, int x, t_ray *r, t_tex_info *tex_info)
{
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;

	tex_x = get_tex_x(exec, r, tex_info);
	step = 1.0 * tex_info->height / r->line_height;
	tex_pos = (r->draw_start - (exec->win_height / 2) + (r->line_height / 2))
		* step;
	tex_info->y = r->draw_start;
	while (tex_info->y < r->draw_end)
	{
		tex_y = (int)tex_pos & (tex_info->height - 1);
		tex_pos += step;
		color = *(int *)(tex_info->img_data + (tex_y * exec->size_line + tex_x
					* (exec->bpp / 8)));
		put_pixel(exec, x, tex_info->y, color);
		tex_info->y++;
	}
}

int	get_tex_x(t_exec *exec, t_ray *r, t_tex_info *tex)
{
	double	wall_x;
	int		tex_x;

	if (r->side == 0)
		wall_x = exec->player.y + r->perp_wall_dist * r->ray_dir_y;
	else
		wall_x = exec->player.x + r->perp_wall_dist * r->ray_dir_x;
	// retourne l'entier le plus grand inferieur ou egal a wall_x
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if ((r->side == 0 && r->ray_dir_x > 0) || (r->side == 1
			&& r->ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

/*
La fonction `floor(wall_x)` retourne la partie entière inférieure de `wall_x` (c’est-à-dire le plus grand entier inférieur ou égal à `wall_x`).
Exemple :
- Si `wall_x = 2.7`, alors `floor(wall_x)` vaut `2.0`.
- Si `wall_x = -1.3`, alors `floor(wall_x)` vaut `-2.0`.
En C, la fonction `floor` est définie dans `<math.h>`.
Elle permet d’obtenir la partie décimale d’un nombre réel en faisant :
```c
```
Ici,
cela sert à ne garder que la partie après la virgule de `wall_x` (pour le calcul de la coordonnée X sur la texture).
*/
