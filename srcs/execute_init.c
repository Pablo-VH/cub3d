#include "cub3D.h"

void	ft_move_ad(t_cub3D *data, t_vectors *vectors, double move_speed)
{
	double	next_x;
	double	next_y;

	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		next_x = vectors->pos_x - vectors->plane_x * move_speed;
		next_y = vectors->pos_y - vectors->plane_y * move_speed;
		if (data->map_arr[(int)(next_x)][(int)(vectors->pos_y)] != '1')
			vectors->pos_x = next_x;
		if (data->map_arr[(int)(vectors->pos_x)][(int)(next_y)] != '1')
			vectors->pos_y = next_y;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		next_x = vectors->pos_x + vectors->plane_x * move_speed;
		next_y = vectors->pos_y + vectors->plane_y * move_speed;
		if (data->map_arr[(int)(next_x)][(int)(vectors->pos_y)] != '1')
			vectors->pos_x = next_x;
		if (data->map_arr[(int)(vectors->pos_x)][(int)(next_y)] != '1')
			vectors->pos_y = next_y;
	}
}

void	ft_move_ws(t_cub3D *data, t_vectors *vectors, double move_speed)
{
	double	next_x;
	double	next_y;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		next_x = vectors->pos_x + vectors->dir_x * move_speed;
		next_y = vectors->pos_y + vectors->dir_y * move_speed;
		if (data->map_arr[(int)(next_x)][(int)(vectors->pos_y)] != '1')
			vectors->pos_x = next_x;
		if (data->map_arr[(int)(vectors->pos_x)][(int)(next_y)] != '1')
			vectors->pos_y = next_y;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		next_x = vectors->pos_x - vectors->dir_x * move_speed;
		next_y = vectors->pos_y - vectors->dir_y * move_speed;
		if (data->map_arr[(int)(next_x)][(int)(vectors->pos_y)] != '1')
			vectors->pos_x = next_x;
		if (data->map_arr[(int)(vectors->pos_x)][(int)(next_y)] != '1')
			vectors->pos_y = next_y;
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
	ft_move_ws(data, data->vectors, move_speed);
	ft_move_ad(data, data->vectors, move_speed);
	handle_mouse_rotation(data);
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
	data->mlx = mlx_init(WIDTH, HEIGHT, "Raycaster MLX42", true);
	if (!data->mlx)
		return (EXIT_FAILURE);
	data->textures = ft_alloc(sizeof(t_texture), 1);
	load_textures(data);
	mlx_image_to_window(data->mlx, data->canvas, 0, 0);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->canvas);
	mlx_delete_texture(data->textures->n);
	mlx_delete_texture(data->textures->s);
	mlx_delete_texture(data->textures->e);
	mlx_delete_texture(data->textures->w);
	mlx_terminate(data->mlx);
	return (0);
}
