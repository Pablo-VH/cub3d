#include "cub3D.h"

void	handle_mouse_rotation(t_cub3D *data)
{
	int		mouse_x;
	int		mouse_y;
	int		center_x;
	double	offset;
	double	rot;
	double	old_dir_x;
	double	old_plane_x;

	mlx_get_mouse_pos(data->mlx, &mouse_x, &mouse_y);
	if (mouse_x < 0 || mouse_x >= WIDTH || mouse_y < 0 || mouse_y >= HEIGHT)
		return;
	center_x = WIDTH / 2;
	offset = (double)(mouse_x - center_x);
	if (fabs(offset) < 2)
		return;
	rot = -offset * 0.003;
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
	mlx_set_mouse_pos(data->mlx, center_x, HEIGHT / 2);
}

