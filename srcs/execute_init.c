#include "cub3D.h"

/*
void draw_column(t_data *data, int x, int drawStart, int drawEnd, int texNum, int texX, int side) {
	for (int y = drawStart; y < drawEnd; y++) {
		int d = y * 256 - HEIGHT * 128 + (drawEnd - drawStart) * 128;
		int texY = ((d * TEX_HEIGHT) / (drawEnd - drawStart)) / 256;
		uint32_t color = data->textures[texNum][TEX_HEIGHT * texY + texX];
		if (side == 1)
			color = (color >> 1) & 0x7F7F7F; // oscurece
		mlx_put_pixel(data->img, x, y, color);
	}
}

void render(void* param) {
	t_data *data = (t_data *)param;

	for (int x = 0; x < WIDTH; x++) {
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = data->dirX + data->planeX * cameraX;
		double rayDirY = data->dirY + data->planeY * cameraX;

		int mapX = (int)data->posX;
		int mapY = (int)data->posY;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double sideDistX, sideDistY;

		int stepX, stepY;
		int hit = 0, side;

		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (data->posX - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
		}
		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (data->posY - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
		}

		while (!hit) {
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (data->worldMap[mapX][mapY] > 0) hit = 1;
		}

		double perpWallDist = (side == 0)
			? (mapX - data->posX + (1 - stepX) / 2) / rayDirX
			: (mapY - data->posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

		int texNum = data->worldMap[mapX][mapY] - 1;

		double wallX = (side == 0)
			? data->posY + perpWallDist * rayDirY
			: data->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)TEX_WIDTH);
		if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
			texX = TEX_WIDTH - texX - 1;

		draw_column(data, x, drawStart, drawEnd, texNum, texX, side);
	}
}*/

static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	(void)mlx;
	//printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

uint32_t	get_rgba(t_rgb colours)
{
	return (colours.r << 24 | colours.g << 16 | colours.b << 8 | 255);
}

void	ft_paint_floor_and_ceiling(t_cub3D *data)
{
	int	color[2];
	int	i;
	int	j;

	data->imgs->floor = mlx_new_image(data->mlx, WIDTH, (HEIGHT / 2));
	data->imgs->ceiling = mlx_new_image(data->mlx, WIDTH, (HEIGHT / 2));
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
	data->imgs = ft_alloc(sizeof(t_img), 1);
	ft_paint_floor_and_ceiling(data);

	/*data->player->posX = 22;
	data->player->posY = 11.5;
	data->player->dirX = -1;
	data->player->dirY = 0;
	data->player->planeX = 0;
	data->player->planeY = 0.66;*/
	mlx_loop_hook(data->mlx, ft_hook, data->mlx);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->imgs->floor);
	mlx_delete_image(data->mlx, data->imgs->ceiling);
	//mlx_delete_texture(texture);
	mlx_terminate(data->mlx);

	//init_map(&data);
	//generate_textures(&data);

	//mlx_loop_hook(data->mlx, &render, &data);
	//mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}