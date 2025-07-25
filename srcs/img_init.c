#include "cub3D.h"

void	load_textures(t_cub3D *data)
{
	data->textures->n = mlx_load_png(data->p_no);
	data->textures->s = mlx_load_png(data->p_so);
	data->textures->e = mlx_load_png(data->p_ea);
	data->textures->w = mlx_load_png(data->p_we);
	if (!data->textures->e || !data->textures->s || !data->textures->w
		|| !data->textures->n)
		ft_terminate_mlx_and_exit(data, 0, "Invalid texture", 99);
	data->canvas = mlx_new_image(data->mlx, WIDTH, HEIGHT);
}
