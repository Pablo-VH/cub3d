#include "cub3D.h"

void    load_textures(t_cub3D *data)
{
    data->textures->n = mlx_load_png("textures/eagle.png");
    data->imgs->n = mlx_texture_to_image(data->mlx, data->textures->n);
    data->textures->s = mlx_load_png("textures/bluestone.png");
    data->imgs->s = mlx_texture_to_image(data->mlx, data->textures->s);
    data->textures->e = mlx_load_png("textures/redbrick.png");
    data->imgs->e = mlx_texture_to_image(data->mlx, data->textures->e);
    data->textures->w = mlx_load_png("textures/greystone.png");
    data->imgs->w = mlx_texture_to_image(data->mlx, data->textures->w);
}
