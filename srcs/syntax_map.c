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

void	charge_map_arr(t_cub3D *data, int size)
{
	int		i;
	t_list	*map;

	data->map_arr = ft_alloc((size + 1) * sizeof(char *), 1);
	map = data->map_lst;
	i = 0;
	while (map)
	{
		data->map_arr[i] = map->content;
		i++;
		map = map->next;
	}
}

void	charge_map_lst(char *line, t_cub3D *data)
{
	t_list	*node;

	if (ft_are_invalid_characters(line, "1 "))
	{
		ft_close_fd_and_exit("Map not properly enclosed by walls", 22, data);
	}
	while (line)
	{
		node = ft_lstnew_p(line);
		ft_lstadd_back(&data->map_lst, node);
		line = ft_strtrim_p(get_next_line_p(data->fd, 0), "\n");
		if (line && ft_are_invalid_characters(line, "01NSEWG "))
			ft_close_fd_and_exit("Invalid character found in map", 21, data);
	}
	get_next_line_p(-1, 1);
	close(data->fd);
	charge_map_arr(data, ft_lstsize(data->map_lst));
}
