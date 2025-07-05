/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:51:56 by pavicent          #+#    #+#             */
/*   Updated: 2025/06/25 12:51:59 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/*
void	check_content(char	**str, t_cub3D *data)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] != '0' && str[i][j] != '1' && str[i][j] != 'N'
				&& str[i][j] != 'W' && str[i][j] != 'S' && str[i][j] != 'E'
				&& str[i][j] != '\n' && str[i][j] != ' ' && str[i][j] != '\0')
				{
					data->err = true;
					return ;
				}
			j++;
		}
		i++;
	}
}

void	copy_map(t_lines *list, t_cub3D *data)
{
	t_lines	*init;
	int		i;

	init = list;
	i = 0;
	while (list->next)
		list = list->next;
	data->init = list->i;
	data->map = ft_alloc(list->i * sizeof(char *), 1);
	list = init;
	while (list)
	{
		data->map[i] = list->str;
		i++;
		list = list->next;
	}
}*/
void	ft_check_adjacent_boxes(char **map, int i, int j, int size)
{
	char	*str;

	str = " \0";
	if ((i != 0 && ft_strchr(str, map[i - 1][j]))
		|| (i < (size - 1) && ft_strchr(str, map[i + 1][j]))
		|| (j != 0 && ft_strchr(str, map[i][j - 1]))
		|| ft_strchr(str, map[i][j + 1])
		|| (i < (size - 1) && (ft_strchr(str, map[i + 1][j + 1])))
		|| (i != 0 && j != 0 && (ft_strchr(str, map[i - 1][j - 1]))))
		ft_print_message_and_exit("Map not properly enclosed by walls", 25);
}

/*void	ft_check_adjacent_boxes2(char **map, int i, int j)
{
	char	*str;

	str = "0NSWE2";
	if ((i != 0 && ft_strchr(str, map[i - 1][j]))
		|| ft_strchr(str, map[i + 1][j])
		|| (j != 0 && ft_strchr(str, map[i][j - 1]))
		|| ft_strchr(str, map[i][j + 1])
		|| ft_strchr(str, map[i + 1][j + 1])
		|| (i != 0 && j != 0 && ft_strchr(str, map[i - 1][j - 1])))
		ft_print_message_and_exit("Map not properly enclosed by walls", 26);
}*/

void	ft_check_walls(char **map, int size)
{
	int		i;
	int		j;
	char	*str;

	str = "0NSWE2";
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((i == 0 && ft_strchr(str, map[i][j]))
				|| (i == size - 1 && ft_strchr(str, map[i][j])))
				ft_print_message_and_exit("Map not properly enclosed by walls", 27);
			if (ft_strchr(str, map[i][j]))
				ft_check_adjacent_boxes(map, i, j, size);
			j++;
		}
		i++;
	}
}


void	ft_check_num_of_players(char *line, int *num_of_players, t_cub3D *data)
{
	int	i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
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

void	charge_map_arr(t_cub3D *data, int size, int len)
{
	int		i;
	t_list	*map;

	data->map_arr = ft_alloc((size + 1) * sizeof(char *), 1);
	map = data->map_lst;
	i = 0;
	while (map)
	{
		data->map_arr[i] = ft_alloc(sizeof(char) * (len + 1), 1);
		ft_strlcpy(data->map_arr[i], map->content, len + 1);
		i++;
		map = map->next;
	}
	ft_check_walls(data->map_arr, size);
}

void	charge_map_lst(char *line, t_cub3D *data)
{
	t_list	*node;
	int		num_of_players;
	size_t	longest_line;

	num_of_players = 0;
	longest_line = 0;
	while (line)
	{
		node = ft_lstnew_p(line);
		ft_lstadd_back(&data->map_lst, node);
		if (*line == '\0')
			ft_close_fd_and_exit("Empty line found in map", 22, data);
		if (ft_are_invalid_characters(line, "01NSEW2 "))
			ft_close_fd_and_exit("Invalid character found in map", 21, data);
		ft_check_num_of_players(line, &num_of_players, data);
		if (longest_line < ft_strlen(line))
			longest_line = ft_strlen(line);
		line = ft_strtrim_p(get_next_line_p(data->fd, 0), "\n");
	}
	if (num_of_players == 0)
		ft_close_fd_and_exit("No player found", 24, data);
	get_next_line_p(-1, 1);
	close(data->fd);
	charge_map_arr(data, ft_lstsize(data->map_lst), longest_line);
}
