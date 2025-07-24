#include "cub3D.h"


void	ft_move_player(t_cub3D *data, t_vectors *vectors, double move_speed)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		vectors->pos_x += vectors->dir_x * move_speed;
		vectors->pos_y += vectors->dir_y * move_speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		vectors->pos_x -= vectors->dir_x * move_speed;
		vectors->pos_y -= vectors->dir_y * move_speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		vectors->pos_x -= vectors->plane_x * move_speed;
		vectors->pos_y -= vectors->plane_y * move_speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		vectors->pos_x += vectors->plane_x * move_speed;
		vectors->pos_y += vectors->plane_y * move_speed;
	}
}

void	ft_rotate(t_cub3D *data, double frame_time)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	old_dir_x = data->vectors->dir_x;
	old_plane_x = data->vectors->plane_x;
	rot = frame_time * 3.0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->vectors->dir_x = data->vectors->dir_x * cos(rot) - data->vectors->dir_y * sin(rot);
		data->vectors->dir_y = old_dir_x * sin(rot) + data->vectors->dir_y * cos(rot);
		data->vectors->plane_x = data->vectors->plane_x * cos(rot) - data->vectors->plane_y * sin(rot);
		data->vectors->plane_y = old_plane_x * sin(rot) + data->vectors->plane_y * cos(rot);
	}	
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		rot = -rot;
		data->vectors->dir_x = data->vectors->dir_x * cos(rot) - data->vectors->dir_y * sin(rot);
		data->vectors->dir_y = old_dir_x * sin(rot) + data->vectors->dir_y * cos(rot);
		data->vectors->plane_x = data->vectors->plane_x * cos(rot) - data->vectors->plane_y * sin(rot);
		data->vectors->plane_y = old_plane_x * sin(rot) + data->vectors->plane_y * cos(rot);
	}
}

void	ft_hook(void *param)
{
	t_cub3D			*data;
	static double	prev_time = 0;
	double			frame_time;
	double			move_speed;
	double			current_time;

	data = (t_cub3D *)param;
	current_time = (double)clock() / CLOCKS_PER_SEC;
	frame_time = current_time - prev_time;
	prev_time = current_time;
	move_speed = frame_time * 5.0;
	ft_move_player(data, data->vectors, move_speed);
	ft_rotate(data, frame_time);
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
	data->imgs = ft_alloc(sizeof(t_img), 1);
	load_textures(data);
	mlx_image_to_window(data->mlx, data->imgs->canvas, 0, 0);
	mlx_loop_hook(data->mlx, ft_hook, data);
	//mlx_key_hook(data->mlx, ft_move, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->imgs->floor);
	mlx_delete_image(data->mlx, data->imgs->ceiling);
	mlx_terminate(data->mlx);
	return (0);
}
