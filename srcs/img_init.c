#include "cub3D.h"

void    load_textures(t_cub3D *data)
{
    data->textures->n = mlx_load_png(data->p_no);
    data->textures->s = mlx_load_png(data->p_so);
    data->textures->e = mlx_load_png(data->p_ea);
    data->textures->w = mlx_load_png(data->p_we);
    if (!data->textures->e || !data->textures->s || !data->textures->w
        || !data->textures->n)
        ft_print_message_and_exit("Invalid texture", 99);
    data->imgs->n = mlx_texture_to_image(data->mlx, data->textures->n);
    data->imgs->s = mlx_texture_to_image(data->mlx, data->textures->s);
    data->imgs->e = mlx_texture_to_image(data->mlx, data->textures->e);
    data->imgs->w = mlx_texture_to_image(data->mlx, data->textures->w);
	data->imgs->canvas = mlx_new_image(data->mlx, WIDTH, HEIGHT);
}
