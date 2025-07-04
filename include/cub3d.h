/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:29:03 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/04 16:46:12 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <unistd.h>

# define ON_DESTROY 17
# define MOVE_SPEED 0.2
# define ROT_SPEED 0.1

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

typedef struct s_exec
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	void		*image;
	char		*img_data;
	int bpp; // profondeur de couleur
	int			size_line;
	int			endian;
	t_player	player;
}				t_exec;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

/*exec_1.c*/
void			ft_exec(int argc, char **argv);
void			init_exec(t_exec *exec);

/*init_mlx.c*/
int				init_mlx(t_exec *exec);
int				handle_window_close(t_exec *exec);

/*draw.c*/
void			create_image(t_exec *exec);
void			draw_something(t_exec *exec, int x_start, int y_start,
					int size);
void			put_pixel(t_exec *exec, int x, int y, int color);

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