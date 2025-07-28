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

uint32_t	get_color(t_vectors *vectors, t_cub3D *data)
{
	int		i;
	uint8_t	*color;

	i = (vectors->tex_y * TEX_WIDTH + vectors->tex_x)
		* data->textures->hit->bytes_per_pixel;
	color = &data->textures->hit->pixels[i];
	return ((color[0] << 24) | (color[1] << 16) | (color[2] << 8) | color[3]);
}

uint32_t	get_rgba(t_rgb colours)
{
	return (colours.r << 24 | colours.g << 16 | colours.b << 8 | 255);
}

void	ft_paint(t_cub3D *data, t_vectors *vectors, int x)
{
	int	y;

	y = 0;
	while (y < vectors->draw_start)
	{
		mlx_put_pixel(data->canvas, x, y, get_rgba(data->c_colours));
		y++;
	}
	ft_print_vertical_line(data, vectors, x);
	y = vectors->draw_end;
	while (y < HEIGHT)
	{
		mlx_put_pixel(data->canvas, x, y, get_rgba(data->f_colours));
		y++;
	}
}

void	ft_clean_images(t_cub3D *data)
{
	mlx_delete_image(data->mlx, data->godz);
	mlx_delete_image(data->mlx, data->canvas);
	mlx_delete_texture(data->textures->godzilla);
	mlx_delete_texture(data->textures->n);
	mlx_delete_texture(data->textures->s);
	mlx_delete_texture(data->textures->e);
	mlx_delete_texture(data->textures->w);
}
