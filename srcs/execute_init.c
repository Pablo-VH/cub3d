#include "cub3D.h"

void	ft_hook(void *param)
{
	t_cub3D	*data;

	data = (t_cub3D *)param;
	ft_print_screen(data, data->vectors);
}

uint32_t	get_rgba(t_rgb colours)
{
	return (colours.r << 24 | colours.g << 16 | colours.b << 8 | 255);
}

void	ft_paint_floor_and_ceiling(t_cub3D *data)
{
	uint32_t	color[2];
	int			i;
	int			j;

	data->imgs->floor = mlx_new_image(data->mlx, WIDTH, (HEIGHT / 2));
	data->imgs->ceiling = mlx_new_image(data->mlx, WIDTH, (HEIGHT / 2));
	if (!data->imgs->floor || !data->imgs->ceiling)
		ft_terminate_mlx_and_exit(data);
	color[0] = get_rgba(data->c_colours);
	color[1] = get_rgba(data->f_colours);
	i = 0;
	while (i < (HEIGHT / 2))
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(data->imgs->ceiling, j, i, color[0]);
			mlx_put_pixel(data->imgs->floor, j, i, color[1]);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->mlx, data->imgs->ceiling, 0, 0);
	mlx_image_to_window(data->mlx, data->imgs->floor, 0, (HEIGHT / 2));
}

int	execute_game(t_cub3D *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "Raycaster MLX42", true);
	if (!data->mlx)
		return (EXIT_FAILURE);
	data->textures = ft_alloc(sizeof(t_texture), 1);
	data->imgs = ft_alloc(sizeof(t_img), 1);
	ft_paint_floor_and_ceiling(data);
	load_textures(data);
	mlx_image_to_window(data->mlx, data->imgs->canvas, 0, 0);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->imgs->floor);
	mlx_delete_image(data->mlx, data->imgs->ceiling);
	mlx_terminate(data->mlx);

	//init_map(&data);
	//generate_textures(&data);

	//mlx_loop_hook(data->mlx, &render, &data);
	//mlx_loop(data->mlx);
	//mlx_terminate(data->mlx);
	return (0);
}
