/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:29:03 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/11 16:07:50 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>

# define ON_DESTROY 17
# define MOVE_SPEED 0.2
# define ROT_SPEED 0.05

typedef struct s_assets
{
	char		**textures;
	char		**colors;
	char		**map;
	int			floor[3];
	int			ceiling[3];
	int			fd;
	int			no_count;
	int			so_count;
	int			we_count;
	int			ea_count;
	int			f_count;
	int			c_count;
	int			map_started;
}				t_assets;

typedef struct s_cub
{
	t_assets	*assets;
}				t_cub;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_ray
{
	double camera_x;  // Position du rayon sur l'axe caméra (de -1 à +1)
	double ray_dir_x; // Composante X de la direction du rayon
	double ray_dir_y; // Composante Y de la direction du rayon

	int map_x; // Case X actuelle de la map que le rayon traverse
	int map_y; // Case Y actuelle de la map que le rayon traverse

	double		side_dist_x;
	// Distance actuelle entre joueur et prochain X de grille
	double		side_dist_y;
	// Distance actuelle entre joueur et prochain Y de grille

	double		delta_dist_x;
	// Distance entre deux X de grille selon la direction du rayon
	double		delta_dist_y;
	// Distance entre deux Y de grille selon la direction du rayon

	double		perp_wall_dist;
	// Distance réelle entre joueur et mur (corrigée pour perspective)

	int step_x; // +1 ou
		// -1 : direction du pas en X (vers la droite ou la gauche)
	int step_y; // +1 ou -1 : direction du pas en Y (vers le haut ou le bas)

	int hit;  // 0 ou 1 : le rayon a-t-il touché un mur ?
	int side; // 0 = mur NS, 1 = mur EW (utile pour choisir la texture/couleur)

	int			line_height;
	// Hauteur de la colonne à dessiner (proportionnelle à distance mur)
	int draw_start; // Y de départ de la colonne murale à dessiner
	int draw_end;   // Y de fin de la colonne murale à dessiner
}				t_ray;

typedef struct s_exec
{
	void		*mlx;
	char		**map;
	int			map_width;
	int			map_height;
	void		*win;
	int			win_width;
	int			win_height;
	void		*image;
	char		*img_data;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;
}				t_exec;

/*exec_1.c*/
void			ft_exec(int argc, char **argv, t_cub *cub);
void			init_exec(t_exec *exec, t_cub *cub);

/*init_mlx.c*/
int				init_mlx(t_exec *exec);
int				handle_window_close(t_exec *exec);

/*draw.c*/
void			create_image(t_exec *exec);
void			draw_something(t_exec *exec, int x_start, int y_start,
					int size);
void			put_pixel(t_exec *exec, int x, int y, int color);
int				render_frame(t_exec *exec);
void			draw_direction(t_exec *exec, int x, int y, double dx,
					double dy);

/*hook.c*/
int				key_hook(int keysym, t_exec *exec);
int				mouse_hook(int mouse_code, t_exec *exec);

/*free.c*/
void			free_exec_exit(t_exec *exec);

int				check_map(char **map);
void			error(char *msg);

/*move_1.c*/
void			move_forward(t_exec *exec);
void			move_backward(t_exec *exec);
void			move_left(t_exec *exec);
void			move_right(t_exec *exec);

/*move_2.c*/
void			rotate(t_exec *exec, double angle);
// void			rotate_right(t_exec *exec);

/*raycasting.c*/
int				render_frame(t_exec *exec);
void			clear_image(t_exec *exec);
void			cast_ray(t_exec *exec, int x);
void			compute_wall(t_exec *exec, t_ray *r);
void			draw_column(t_exec *exec, int x, t_ray *r);
/*raycasting_init.c*/
void			init_ray(t_exec *exec, t_ray *r, int x);
void			init_steps(t_exec *exec, t_ray *r);
void			perform_dda(t_exec *exec, t_ray *r);

/* FUNCTIONS */
int				check_all_textures_present(t_assets *assets);
int				check_color_duplicates(t_assets *assets, char *line);
int				check_texture_duplicates(t_assets *assets, char *line);
void			free_array(char **array);
void			free_assets(t_assets *assets);
int				read_map(t_assets *assets);
int				is_map(char *line);
int				is_color(char *line);
int				is_texture(char *line);
t_assets		*parse_map(t_cub *cub, char **argv);
int				c_strchr(char *str, char *s);
void			print_cub3d(void);

#endif