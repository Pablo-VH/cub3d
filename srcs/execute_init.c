/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:40:14 by pavicent          #+#    #+#             */
/*   Updated: 2025/07/29 11:40:15 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_check_collision(t_cub3D *data, t_vectors *vectors)
{
	if (data->map_arr[(int)(vectors->next_x)][(int)(vectors->pos_y)] != '1'
		&& data->map_arr[(int)(vectors->next_x)][(int)(vectors->pos_y)] != ' ')
		vectors->pos_x = vectors->next_x;
	if (data->map_arr[(int)(vectors->pos_x)][(int)(vectors->next_y)] != '1'
		&& data->map_arr[(int)(vectors->pos_x)][(int)(vectors->next_y)] != ' ')
		vectors->pos_y = vectors->next_y;
}

void	ft_move(t_cub3D *data, t_vectors *vectors, double move_speed)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		vectors->next_x = vectors->pos_x - vectors->plane_x * move_speed;
		vectors->next_y = vectors->pos_y - vectors->plane_y * move_speed;
		ft_check_collision(data, vectors);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		vectors->next_x = vectors->pos_x + vectors->plane_x * move_speed;
		vectors->next_y = vectors->pos_y + vectors->plane_y * move_speed;
		ft_check_collision(data, vectors);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		vectors->next_x = vectors->pos_x + vectors->dir_x * move_speed;
		vectors->next_y = vectors->pos_y + vectors->dir_y * move_speed;
		ft_check_collision(data, vectors);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		vectors->next_x = vectors->pos_x - vectors->dir_x * move_speed;
		vectors->next_y = vectors->pos_y - vectors->dir_y * move_speed;
		ft_check_collision(data, vectors);
	}
}

void	ft_rotate(t_vectors *vectors, double frame_time, int direction)
{
	double	prev_dir_x;
	double	prev_plane_x;
	double	rotspeed;

	prev_dir_x = vectors->dir_x;
	prev_plane_x = vectors->plane_x;
	rotspeed = frame_time * 3.0;
	rotspeed = -fabs(rotspeed);
	if (direction)
		rotspeed = fabs(rotspeed);
	vectors->dir_x = vectors->dir_x * cos(rotspeed)
		- vectors->dir_y * sin(rotspeed);
	vectors->dir_y = prev_dir_x * sin(rotspeed)
		+ vectors->dir_y * cos(rotspeed);
	vectors->plane_x = vectors->plane_x * cos(rotspeed)
		- vectors->plane_y * sin(rotspeed);
	vectors->plane_y = prev_plane_x * sin(rotspeed)
		+ vectors->plane_y * cos(rotspeed);
}

void	ft_hook(void *param)
{
	t_cub3D			*data;
	static double	prev_time = 0;
	double			frame_time;
	double			move_speed;
	double			current_time;

	data = (t_cub3D *)param;
	current_time = mlx_get_time();
	frame_time = current_time - prev_time;
	prev_time = current_time;
	move_speed = frame_time * 5.0;
	ft_move(data, data->vectors, move_speed);
	handle_mouse_rotation(data);
	ft_door(data, data->vectors);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		ft_rotate(data->vectors, frame_time, 1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		ft_rotate(data->vectors, frame_time, 0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	ft_print_screen(data, data->vectors);
}

int	execute_game(t_cub3D *data)
{
	data->input = ft_alloc(sizeof(t_input), 1);
	data->mlx = mlx_init(WIDTH, HEIGHT, "DOOMZILLA", true);
	if (!data->mlx)
		return (EXIT_FAILURE);
	data->textures = ft_alloc(sizeof(t_texture), 1);
	load_textures(data);
	data->textures->godzilla = mlx_load_png("textures/Manos.png");
	data->godz = mlx_texture_to_image(data->mlx, data->textures->godzilla);
	mlx_image_to_window(data->mlx, data->canvas, 0, 0);
	mlx_image_to_window(data->mlx, data->godz, 0, 0);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	ft_clean_images(data);
	mlx_terminate(data->mlx);
	return (0);
}
