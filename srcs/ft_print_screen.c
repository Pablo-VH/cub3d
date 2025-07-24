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
		else{
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
	vectors->perp_wall_dist = vectors->side_dist_x - vectors->delta_dist_x;
	if (vectors->side)
		vectors->perp_wall_dist = vectors->side_dist_y - vectors->delta_dist_y;
}

uint32_t	get_color(t_vectors *vectors, t_cub3D *data)
{
	int		i;
	uint8_t	*color;

	i = (vectors->tex_y * TEX_WIDTH + vectors->tex_x)
		* data->textures->hit->bytes_per_pixel;
	color = &data->textures->hit->pixels[i];
	return ((color[0] << 24) | (color[1] << 16) | (color[2] << 8) |color[3]);
}

void	ft_print_vertical_line(t_cub3D *data, t_vectors *vectors, uint32_t x)
{
	uint32_t	color;
	double		step;
	int			y;

	step = ((double)TEX_HEIGHT / (double)vectors->line_height);
	vectors->tex_pos = (vectors->draw_start - HEIGHT
		/ 2 + vectors->line_height /2) * step;
	y = vectors->draw_start;
	while (y < vectors->draw_end)
	{
		vectors->tex_y = (int)vectors->tex_pos & (TEX_HEIGHT - 1);
		vectors->tex_pos += step;
		color = get_color(vectors, data);
		mlx_put_pixel(data->imgs->canvas, x, (uint32_t)y, color);
		y++;
	}
}

uint32_t	get_rgba(t_rgb colours)
{
	return (colours.r << 24 | colours.g << 16 | colours.b << 8 | 255);
}

void	print_columns(t_cub3D *data, t_vectors *vectors, uint32_t x)
{
	vectors->line_height = (int)(HEIGHT / vectors->perp_wall_dist);
	//printf("line_height = %d\n", vectors->line_height);
	vectors->draw_start = -(vectors->line_height) / 2 + HEIGHT / 2;
	if (vectors->draw_start < 0)
	vectors->draw_start = 0;
	vectors->draw_end = vectors->line_height / 2 + HEIGHT / 2;
	if (vectors->draw_end >= HEIGHT)
		vectors->draw_end = HEIGHT - 1;
	vectors->wall_x = vectors->pos_y
		+ vectors->perp_wall_dist * vectors->ray_dir_y;
	if (vectors->side)
		vectors->wall_x = vectors->pos_x
			+ vectors->perp_wall_dist * vectors->ray_dir_x;
	vectors->wall_x -= floor(vectors->wall_x);
	vectors->tex_x = (int)(vectors->wall_x * (double)TEX_WIDTH);
	if ((vectors->side == 0 && vectors->ray_dir_x > 0)
		|| (vectors->side == 1 && vectors->ray_dir_y < 0))
		vectors->tex_x = TEX_WIDTH - vectors->tex_x - 1;
	int	y;
	y = 0;
	while (y < vectors->draw_start)
	{
		mlx_put_pixel(data->imgs->canvas, x, y, get_rgba(data->c_colours));
		y++;
	}
	ft_print_vertical_line(data, vectors, x);
	y = vectors->draw_end;
	while (y < HEIGHT)
	{
		mlx_put_pixel(data->imgs->canvas, x, y, get_rgba(data->f_colours));
		y++;
	}
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
		//printf("pos_x = %lf | pos_y = %lf | dir_x = %lf | dir_y = %lf | plane_x = %lf | plane_y = %lf\n", data->vectors->pos_x, data->vectors->pos_y, data->vectors->dir_x, data->vectors->dir_y, data->vectors->plane_x, data->vectors->plane_y);
		vectors->camera_x = 2 * x / (double)WIDTH - 1;
		//printf("camera_x = %lf\n", vectors->camera_x);
		vectors->ray_dir_x = vectors->dir_x
			+ vectors->plane_x * vectors->camera_x;
		//printf("ray_dir_x = %lf\n", vectors->ray_dir_x);
		vectors->ray_dir_y = vectors->dir_y
			+ vectors->plane_y * vectors->camera_x;
		//printf("ray_dir_y = %lf\n", vectors->ray_dir_y);
		vectors->map_x = (int)vectors->pos_x;
		vectors->map_y = (int)vectors->pos_y;
		vectors->delta_dist_x = 1e30;
		if (vectors->ray_dir_x != 0)
			vectors->delta_dist_x = fabs(1 / vectors->ray_dir_x);
		vectors->delta_dist_y = 1e30;
		if (vectors->ray_dir_y != 0)
			vectors->delta_dist_y = fabs(1 / vectors->ray_dir_y);

		//printf("ray_dir_y: %lf | ray_dir_x: %lf\n", vectors->ray_dir_y, vectors->ray_dir_x);
		ft_get_side_dist(vectors);
		find_distance_to_walls(data, data->vectors);
		print_columns(data, data->vectors, x);
		x++;
	}
}

/*
for(int x = 0; x < w; x++)
    {
      //calculate ray position and direction
      double cameraX = 2*x/double(w)-1; //x-coordinate in camera space
      double rayDirX = dirX + planeX*cameraX;
      double rayDirY = dirY + planeY*cameraX;

      //which box of the map we're in
      int mapX = int(posX);
      int mapY = int(posY);

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
      double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
      if (rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if (rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
	while (hit == 0)
    {
        //jump to next map square, either in x-direction, or in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if(worldMap[mapX][mapY] > 0) hit = 1;
      }
	}
	*/