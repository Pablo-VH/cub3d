#include "cub3D.h"

void	ft_door(t_cub3D *data, t_vectors *vectors)
{
	int	target_x;
	int	target_y;

	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
	{
		target_x = (int)vectors->dir_x + vectors->pos_x;
		target_y = (int)vectors->dir_y + vectors->pos_y;
		if (data->map_arr[target_x][target_y] == '2')
			data->map_arr[target_x][target_y] = '3';
		if (data->map_arr[target_x][target_y] == '3')
			data->map_arr[target_x][target_y] = '2';
	}
}

void	handle_mouse_rotation(t_cub3D *data)
{
	double	rot;
	double	old_dir_x;
	double	old_plane_x;

	mlx_get_mouse_pos(data->mlx, &data->mouse_x, &data->mouse_y);
	if (data->mouse_x < 0 || data->mouse_x >= WIDTH
		|| data->mouse_y < 0 || data->mouse_y >= HEIGHT)
		return ;
	data->center_x = WIDTH / 2;
	data->offset = (double)(data->mouse_x - data->center_x);
	if (fabs(data->offset) < 2)
		return ;
	rot = -data->offset * 0.003;
	old_dir_x = data->vectors->dir_x;
	data->vectors->dir_x = data->vectors->dir_x * cos(rot)
		- data->vectors->dir_y * sin(rot);
	data->vectors->dir_y = old_dir_x * sin(rot)
		+ data->vectors->dir_y * cos(rot);
	old_plane_x = data->vectors->plane_x;
	data->vectors->plane_x = data->vectors->plane_x * cos(rot)
		- data->vectors->plane_y * sin(rot);
	data->vectors->plane_y = old_plane_x * sin(rot)
		+ data->vectors->plane_y * cos(rot);
	mlx_set_mouse_pos(data->mlx, data->center_x, HEIGHT / 2);
}
