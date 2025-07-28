#include "cub3D.h"

void	find_distance_to_walls(t_cub3D *data, t_vectors *vectors)
{
	while (1)
	{
		if (vectors->side_dist_x < vectors->side_dist_y)
		{
			vectors->side_dist_x += vectors->delta_dist_x;
			vectors->map_x += vectors->step_x;
			vectors->side = 0;
			data->textures->hit = data->textures->n;
			if (vectors->ray_dir_x < 0)
				data->textures->hit = data->textures->s;
		}
		else
		{
			vectors->side_dist_y += vectors->delta_dist_y;
			vectors->map_y += vectors->step_y;
			vectors->side = 1;
			data->textures->hit = data->textures->e;
			if (vectors->ray_dir_y > 0)
				data->textures->hit = data->textures->w;
		}
		if (data->map_arr[vectors->map_x][vectors->map_y] == '1')
			break ;
	}
	vectors->perp_dist = vectors->side_dist_x - vectors->delta_dist_x;
}

void	ft_print_vertical_line(t_cub3D *data, t_vectors *vectors, uint32_t x)
{
	uint32_t	color;
	double		step;
	int			y;

	step = ((double)TEX_HEIGHT / (double)vectors->line_height);
	vectors->tex_pos = (vectors->draw_start - HEIGHT
			/ 2 + vectors->line_height / 2) * step;
	y = vectors->draw_start;
	while (y < vectors->draw_end)
	{
		vectors->tex_y = (int)vectors->tex_pos & (TEX_HEIGHT - 1);
		vectors->tex_pos += step;
		color = get_color(vectors, data);
		mlx_put_pixel(data->canvas, x, (uint32_t)y, color);
		y++;
	}
}

void	print_columns(t_cub3D *data, t_vectors *vectors, uint32_t x)
{
	vectors->line_height = (int)(HEIGHT / vectors->perp_dist);
	vectors->draw_start = -(vectors->line_height) / 2 + HEIGHT / 2;
	if (vectors->draw_start < 0)
		vectors->draw_start = 0;
	vectors->draw_end = vectors->line_height / 2 + HEIGHT / 2;
	if (vectors->draw_end >= HEIGHT)
		vectors->draw_end = HEIGHT - 1;
	vectors->wall_x = vectors->pos_y
		+ vectors->perp_dist * vectors->ray_dir_y;
	if (vectors->side)
		vectors->wall_x = vectors->pos_x
			+ vectors->perp_dist * vectors->ray_dir_x;
	vectors->wall_x -= floor(vectors->wall_x);
	vectors->tex_x = (int)(vectors->wall_x * (double)TEX_WIDTH);
	if ((vectors->side == 0 && vectors->ray_dir_x > 0)
		|| (vectors->side == 1 && vectors->ray_dir_y < 0))
		vectors->tex_x = TEX_WIDTH - vectors->tex_x - 1;
	ft_paint(data, vectors, x);
}

void	ft_get_side_dist(t_vectors *vectors)
{
	if (vectors->ray_dir_x < 0)
	{
		vectors->step_x = -1;
		vectors->side_dist_x = (vectors->pos_x
				- vectors->map_x) * vectors->delta_dist_x;
	}
	else
	{
		vectors->step_x = 1;
		vectors->side_dist_x = (vectors->map_x + 1.0
				- vectors->pos_x) * vectors->delta_dist_x;
	}
	if (vectors->ray_dir_y < 0)
	{
		vectors->step_y = -1;
		vectors->side_dist_y = (vectors->pos_y
				- vectors->map_y) * vectors->delta_dist_y;
	}
	else
	{
		vectors->step_y = 1;
		vectors->side_dist_y = (vectors->map_y + 1.0
				- vectors->pos_y) * vectors->delta_dist_y;
	}
}

void	ft_print_screen(t_cub3D *data, t_vectors *vectors)
{
	uint32_t	x;

	x = 0;
	while (x < WIDTH)
	{
		vectors->camera_x = 2 * x / (double)WIDTH - 1;
		vectors->ray_dir_x = vectors->dir_x
			+ vectors->plane_x * vectors->camera_x;
		vectors->ray_dir_y = vectors->dir_y
			+ vectors->plane_y * vectors->camera_x;
		vectors->map_x = (int)vectors->pos_x;
		vectors->map_y = (int)vectors->pos_y;
		vectors->delta_dist_x = 1e30;
		if (vectors->ray_dir_x != 0)
			vectors->delta_dist_x = fabs(1 / vectors->ray_dir_x);
		vectors->delta_dist_y = 1e30;
		if (vectors->ray_dir_y != 0)
			vectors->delta_dist_y = fabs(1 / vectors->ray_dir_y);
		ft_get_side_dist(vectors);
		find_distance_to_walls(data, data->vectors);
		if (vectors->side)
			vectors->perp_dist = vectors->side_dist_y - vectors->delta_dist_y;
		print_columns(data, data->vectors, x);
		x++;
	}
}
