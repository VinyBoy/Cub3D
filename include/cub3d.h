/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:29:03 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/04 14:11:35 by oztozdem         ###   ########.fr       */
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

int				check_map(char **map);
void			error(char *msg);

/* FUNCTIONS */
int	check_all_textures_present(t_assets *assets);
int	check_color_duplicates(t_assets *assets, char *line);
int	check_texture_duplicates(t_assets *assets, char *line);
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