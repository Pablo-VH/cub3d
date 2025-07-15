/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:20:32 by pavicent          #+#    #+#             */
/*   Updated: 2025/06/24 19:20:34 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/*
void	take_player_values(t_cub3D *data, int x, int y)
{
	data->player->posX = x + 0.5;
	data->player->posY = y + 0.5;
	if (data->map_arr[y][x] == 'N')
	{
		data->player->dirX = 0;
		data->player->dirY = -1;
		data->player->planeX = 0.66;
		data->player->planeY = 0;
	}
	else if (data->map_arr[y][x] == 'S')
	{
		data->player->dirX = 0;
		data->player->dirY = 1;
		data->player->planeX = -0.66;
		data->player->planeY = 0;
	}
	else if (data->map_arr[y][x] == 'E')
	{
		data->player->dirX = 1;
		data->player->dirY = 0;
		data->player->planeX = 0;
		data->player->planeY = 0.66;
	}
	else if (data->map_arr[y][x] == 'W')
	{
		data->player->dirX = -1;
		data->player->dirY = 0;
		data->player->planeX = 0;
		data->player->planeY = -0.66;
	}
}

void	set_player_pos(char **map, t_player *player, t_cub3D *data)
{
	int		x;
	int		y;
	char	*str;
	(void)player;

	y = 0;
	str = "NSWE";
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr(str, map[y][x]))
				return (take_player_values(data, x, y)) ;
			x++;
		}
		y++;
	}
	
}*/

int	main(int ac, char **av)
{
	t_cub3D	*data;

	if (ac != 2)
		ft_print_message_and_exit("Incorrect number of arguments", 1);
	if (!ft_check_extention(av[1], ".cub"))
		ft_print_message_and_exit("Not valid .cub extention", 1);
	data = ft_alloc(sizeof(t_cub3D), 1);
	parsing(av[1], data);
//	set_player_pos(data->map_arr, data->player, data);
	execute_game(data);
	ft_alloc(0, 0);
}
