#include "cub3D.h"

void	find_distance_to_walls(t_cub3D *data, t_vectors *vectors)
{
	while (1)
	{
		if (vectors->side_dist_x < vectors->side_dist_y)
        {
			vectors->side_dist_x += vectors->delta_dist_x;
			vectors->map_y += vectors->step_x;
			vectors->side = 0; //probablemente haya que intercambiar estos valores
		}
        else
        {
            vectors->side_dist_y += vectors->delta_dist_y;
            vectors->map_y += vectors->step_y;
            vectors->side = 1;
        }
		if (data->map_arr[vectors->map_y][vectors->map_x] > 0) // check if map_y must be in the second dimension
			break ;
	}
	vectors->perp_wall_dist = vectors->side_dist_x - vectors->delta_dist_x;
	if (vectors->side)
		vectors->perp_wall_dist = vectors->side_dist_y - vectors->delta_dist_y;
}

void	print_columns(t_cub3D *data, t_vectors *vectors)
{
	uint32_t	buffer[HEIGHT][WIDTH];
	int			*textures[4];
	int			i;

	vectors->line_height = (int)(HEIGHT / vectors->perp_wall_dist);
	vectors->draw_start = -vectors->line_height / 2 + HEIGHT / 2;
	if (vectors->draw_start < 0)
		vectors->draw_start = 0;
	vectors->draw_end = vectors->line_height / 2 + HEIGHT / 2;
	if (vectors->draw_end >= HEIGHT)
		vectors->draw_end = -1;
	i = 0;
	while (i < 4)
	{
		textures[i] = ft_alloc(TEX_HEIGHT * TEX_WIDTH * sizeof(int), 1);
		i++;
	}
	vectors->text_num = data->map_arr[vectors->map_x][vectors->map_y] - 1;
	vectors->wall_x = vectors->pos_x + vectors->perp_wall_dist * vectors->ray_dir_x;
	if (vectors->side == 0)
		vectors->wall_x = vectors->pos_y + vectors->perp_wall_dist * vectors->ray_dir_y;
	vectors->wall_x -= floor(vectors->wall_x);
	vectors->text_x = (int)(vectors->wall_x * (double)TEX_WIDTH);
	if ((vectors->side == 0 && vectors->ray_dir_x > 0)
		|| (vectors->side == 1 && vectors->ray_dir_x < 0))
		vectors->text_x = TEX_WIDTH - vectors->text_x - 1;
	vectors->step = 1.0 * TEX_HEIGHT / vectors->line_height;
	vectors->text_pos = (vectors->draw_start - HEIGHT / 2 + vectors->line_height / 2) * vectors->step;
	i = vectors->draw_start;
	while (i < vectors->draw_end)
	{
		vectors->text_y = (int)vectors->text_pos & (TEX_HEIGHT - 1);
		vectors->text_pos += vectors->step;
		vectors->color = textures[vectors->text_num][TEX_HEIGHT * vectors->text_y + vectors->text_x];
	}
}

void	ft_print_screen(t_cub3D *data, t_vectors *vectors)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		vectors->camera_x = 2 * x / (double)WIDTH - 1;
		vectors->ray_dir_x = vectors->dir_x + vectors->plane_x * vectors->camera_x;
		vectors->ray_dir_y = vectors->dir_y + vectors->plane_y * vectors->camera_x;
		vectors->map_x = (int)vectors->pos_x; //intercambiar los valores de x e y si es preciso
		vectors->map_y = (int)vectors->pos_y;
		vectors->delta_dist_x = abs(1 / vectors->ray_dir_x);
		vectors->delta_dist_y = abs(1 / vectors->ray_dir_y); 
		if (vectors->ray_dir_x < 0)
		{
			vectors->step_x = -1;
			vectors->side_dist_x = (vectors->pos_x - (double)vectors->map_x) * vectors->delta_dist_x;
		}
		else
		{
			vectors->step_x = 1;
			vectors->side_dist_x = ((double)vectors->map_x + 1.0 - vectors->pos_x) * vectors->delta_dist_x;
		}
		if (vectors->ray_dir_y < 0)
		{
			vectors->step_y = -1;
			vectors->side_dist_y = (vectors->pos_y + (double)vectors->map_y) * vectors->delta_dist_y;
		}
		else
		{
			vectors->step_y = 1;
			vectors->side_dist_y = ((double)vectors->map_y + 1.0 - vectors->pos_y) * vectors->delta_dist_y;
		}
		x++;
	}
	find_distance_to_walls(data, data->vectors);
	print_columns(data, data->vectors);
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