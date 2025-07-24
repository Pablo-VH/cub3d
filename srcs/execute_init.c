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

void	ft_rotate(t_vectors *vectors, double frame_time, int direction)//!!!!!CUANDO EL JUJADOR EMPIEZA EN N O E ROTA EN EL SENTIDO CONTRARIO QUE SI EMPIEZA EN S O W!!!!!!!!!!!
{
	double	prev_dir_x;
	double	prev_plane_x;
	double	rotspeed;

	prev_dir_x = vectors->dir_x;
	prev_plane_x = vectors->plane_x;
	rotspeed = frame_time * 3.0;
	if (direction)
		rotspeed = -rotspeed;
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
	current_time = (double)clock() / CLOCKS_PER_SEC;//!!!!FUNCION PROHIBIDA!!!!!!!
	frame_time = current_time - prev_time;
	prev_time = current_time;
	move_speed = frame_time * 5.0;
	ft_move_player(data, data->vectors, move_speed);
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
	data->imgs = ft_alloc(sizeof(t_img), 1);
	load_textures(data);
	mlx_image_to_window(data->mlx, data->imgs->canvas, 0, 0);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->imgs->floor);
	mlx_delete_image(data->mlx, data->imgs->ceiling);
	mlx_terminate(data->mlx);
	return (0);
}
