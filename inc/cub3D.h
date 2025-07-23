/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:05:09 by pavicent          #+#    #+#             */
/*   Updated: 2025/06/25 12:05:10 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/time.h>
# include "../libft/libft.h"
# include "MLX42.h"

# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;97m"
# define RESET "\033[0m"
# define WIDTH 640
# define HEIGHT 480
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MOVESPEED 0.0125
# define ROTSPEED 0.015

typedef enum s_states
{
	N_ERR,
	N_NUM,
	N_SYM,
	N_SPA,
	N_SP2,
}	t_states;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}		t_rgb;

typedef struct s_vectors
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		wall_x;
	int			map_x;
	int			map_y;
	int			draw_start;
	int			draw_end;
	int			line_height;
	int			tex_num;
	int			tex_x;
	int			tex_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	double		step;
	double		tex_pos;
	int			step_x;
	int			step_y;
	int			side;
	uint32_t	color;
}			t_vectors;

typedef struct s_img
{
	mlx_image_t		*ceiling;
	mlx_image_t		*floor;
	mlx_image_t		*n;
	mlx_image_t		*s;
	mlx_image_t		*e;
	mlx_image_t		*w;	
	mlx_image_t		*canvas;
//	mlx_image_t		*hit;
}				t_img;

typedef struct	s_textures
{
	mlx_texture_t	*n;
	mlx_texture_t	*s;
	mlx_texture_t	*e;
	mlx_texture_t	*w;
	mlx_texture_t	*hit;
}				t_texture;

typedef struct s_cub3D
{
	t_list		*file;
	t_rgb		f_colours;
	t_rgb		c_colours;
	t_list		*map_lst;
	//t_player	*player;
	//t_ray		*ray;
	t_vectors	*vectors;
	mlx_t		*mlx;
	t_img		*imgs;
	t_texture	*textures;
	char		**map_arr;
	char		*p_no;
	char		*p_so;
	char		*p_we;
	char		*p_ea;
	int			fd;
}				t_cub3D;
// if side == 0 we are looking to the East.
// if side == 1 we are looking to the North.
// if side == 2 we are looking to the Weast.
// if side == 3 we are looking to the South.


int		ft_are_invalid_characters(char *line, char *valid_characters);
void	charge_color_data(int n, t_rgb *colors, char *line, t_cub3D *data);
void	charge_color_info(char *line, t_rgb *colors, char *def, t_cub3D *data);
void	charge_map_lst(char *line, t_cub3D *data);
void	charge_t_info(char *line, char **recipient, char *def, t_cub3D *data);
void	check_num(char **line, t_cub3D *data);
int		execute_game(t_cub3D *data);
void	ft_check_num_of_playrs(char *line, int *num_of_players, t_cub3D *data);
void	ft_check_walls(char **map, int size);
void	ft_close_fd_and_exit(char *s, int exit_key, t_cub3D *data);
void	ft_perror_and_exit(char *s, int exit_key);
void	ft_print_message_and_exit(char *s, int exit_key);
void	ft_print_screen(t_cub3D *data, t_vectors *vectors);
void	ft_terminate_mlx_and_exit(t_cub3D *data);
void    load_textures(t_cub3D *data);
void	parsing(char *av, t_cub3D *data);

#endif
