/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:29:03 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/04 16:58:34 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <unistd.h>

typedef struct s_assets
{
	char		**textures;
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

/* PARSING */

/* check.c */
int				check_content(char **map);
int				all_info_complete(t_assets *assets);
int				check_map(char **map);

/* color.c */
int				count_commas(char *str);
int				is_valid_number(char *str);
int				parse_color(char *color_str, int *rgb);
int				store_color(t_assets *assets, char *line);

/* duplicate.c */
int				check_texture_duplicates(t_assets *assets, char *line);
int				check_color_duplicates(t_assets *assets, char *line);
int				check_all_textures_present(t_assets *assets);

/* free.c */
void			free_array(char **array);
void			free_assets(t_assets *assets);

/* parsing.c */
void			copy_with_single_spaces(char *line, char *c_line, int *i,
					int *j);
char			*clean_line(char *line);
char			**line_to_array(char **array, char *line, int *size);
int				read_map(t_assets *assets);
int				parsing(t_assets *assets);
t_assets		*parse_map(t_cub *cub, char **argv);

/* print.c */
void			print_array(char **array);
void			print_floor(int tab[3]);
void			print_ceiling(int tab[3]);
void			print_assets(t_assets *assets);

/* parsing/utils.c */
int				is_texture(char *line);
int				is_color(char *line);
int				is_map(char *line);

/* fill_map.c */
int				get_max_line_len(char **map);
char			*fill_line(char *line, int target_length);
char			**fill_map(char **map);

/* UTILS */

/* ./utils.c */
void			print_cub3d(void);
void			error(char *msg);
int				c_strchr(char *str, char *s);

#endif