/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:51:56 by pavicent          #+#    #+#             */
/*   Updated: 2025/06/25 12:51:59 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_check_adjacent_boxes(char **map, int i, int j, int size)
{
	char	*str;

	str = " \0";
	if ((i != 0 && ft_strchr(str, map[i - 1][j]))
		|| (i < (size - 1) && ft_strchr(str, map[i + 1][j]))
		|| (j != 0 && ft_strchr(str, map[i][j - 1]))
		|| ft_strchr(str, map[i][j + 1])
		|| (i < (size - 1) && (ft_strchr(str, map[i + 1][j + 1])))
		|| ((i != 0 && j != 0) && (ft_strchr(str, map[i - 1][j - 1])))
		|| ((i < size -1 && j != 0) && (ft_strchr(str, map[i + 1][j - 1])))
		|| ((i != 0) && (ft_strchr(str, map[i - 1][j + 1]))))
		ft_print_message_and_exit("Map not properly enclosed by walls", 25);
}

void	ft_check_walls(char **map, int size)
{
	int		i;
	int		j;
	char	*str;

	str = "0NSWE";
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((i == 0 && ft_strchr(str, map[i][j]))
				|| (j == 0 && ft_strchr(str, map[i][j]))
				|| (i == size - 1 && ft_strchr(str, map[i][j])))
				ft_print_message_and_exit
					("Map not properly enclosed by walls", 27);
			if (ft_strchr(str, map[i][j]))
				ft_check_adjacent_boxes(map, i, j, size);
			j++;
		}
		i++;
	}
}

void	ft_check_num_of_playrs(char *line, int *num_of_players, t_cub3D *data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			(*num_of_players)++;
		i++;
	}
	if (*num_of_players > 1)
		ft_close_fd_and_exit("Too many players found in map", 23, data);
}

int	ft_are_invalid_characters(char *line, char *valid_characters)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(valid_characters, line[i]))
			return (1);
		i++;
	}
	return (0);
}
