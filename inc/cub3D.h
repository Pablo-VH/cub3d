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

typedef enum s_fc
{
	FLOOR,
	CEILING
}	t_fc;

typedef enum s_states
{
	N_ERR,
	N_NUM,
	N_SYM,
	N_SPA,
	N_SP2,
}	t_states;

typedef struct s_lines
{
	int				i;
	char			*str;
	struct s_lines	*next;
}					t_lines;

/*typedef struct s_floor
{
	char	*setter;
	int		r;
	int		g;
	int		b;
}		t_floor;

typedef struct s_ceiling
{
	int	r;
	int	g;
	int	b;
}		t_ceiling;*/

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}		t_rgb;

typedef struct s_cub3D
{
	t_lines		*file;
	t_rgb		f_colours;
	t_rgb		c_colours;
	t_list		*map_lst;
	char		**map_arr;
	char		*p_no;
	char		*p_so;
	char		*p_we;
	char		*p_ea;
	int			fd;
	//int			no;
	//int			so;
	//int			we;
	//int			ea;
	//int			f;
	//int			c;
	int			init;
	int			max_len;
	bool		err;
}				t_cub3D;

void	charge_color_data(int n, t_rgb *colors, char *line, t_cub3D *data);
void	check_elements(char *line);
void	charge_info(t_cub3D *data);
//void	check_colors(t_cub3D *data);
//void	check_content(char	**str, t_cub3D *data);
void	check_file(char *av, t_cub3D *data);
void	check_map(char *av, t_cub3D *data);
void	check_num(char **line, t_cub3D *data);
void	charge_map_lst(char *line, t_cub3D *data);
//void	take_fc(char *colours, t_cub3D *data, int flag);
//void	get_path(char *path, char *to_take);
void	ft_close_fd_and_exit(char *s, int exit_key, t_cub3D *data);
void	ft_perror_and_exit(char *s, int exit_key);
void	ft_print_message_and_exit(char *s, int exit_key);

#endif
