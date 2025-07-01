/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:04:11 by pavicent          #+#    #+#             */
/*   Updated: 2025/06/25 12:04:14 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_elements2(t_lines *list, t_cub3D *data)
{

	if (!ft_strncmp(list->str, "WE ", 3))
	{
		data->we++;
		take_path(data->p_we, list->str);
	}
	else if (!ft_strncmp(list->str, "EA ", 3))
	{
		data->ea++;
		take_path(data->p_ea, list->str);
	}
}

void	check_fc(t_lines *list, t_cub3D *data)
{
	while (list)
	{
		if (!ft_strncmp(list->str, "C ", 2))
		{
			data->c++;
			take_fc(list->str, data, CEILING);
		}
		if (!ft_strncmp(list->str, "F ", 2))
		{
			data->f++;
			take_fc(list->str, data, FLOOR);
		}
		if (ft_strncmp(list->str, "C ", 2) && ft_strncmp(list->str, "F ", 2)
			&& ft_strncmp(list->str, "NO ", 3) && ft_strncmp(list->str, "SO ", 3)
			&& ft_strncmp(list->str, "WE ", 3) && ft_strncmp(list->str, "EA ", 3)
			&& ft_strncmp(list->str, "\n", 2))
			break ;
		list = list->next;
	}
	if (data->f != 1 || data->c != 1)
		ft_print_message_and_exit("Invalid parameters", 4);
	check_colors(data);
	
}

void	check_intro(t_lines *list)
{
	int	i;

	while (list)
	{
		i = 0;
		while (list->str[i] && ft_isspace(list->str[i]))
			i++;
		if (list->str[i])
			break ;
		list = list->next;
	}
}

void	check_elements(t_lines *list, t_cub3D *data)
{
	while (list)
	{
		if (!ft_strncmp(list->str, "NO ", 3))
		{
			data->no++;
			take_path(data->p_no, list->str);
		}
		else if (!ft_strncmp(list->str, "SO ", 3))
		{
			data->so++;
			take_path(data->p_so, list->str);
		}
		else
			check_elements2(list, data);
		list = list->next;
	}
	if (data->no != 1 || data->so != 1 || data->we != 1 || data->ea != 1)
		ft_print_message_and_exit("Invalid parameters", 3);
}

void	check_map(char *av, t_cub3D *data)
{
	t_lines	*init;

	check_file(av, data);
	init = data->file;
	check_elements(data->file, data);
	data->file = init;
	check_fc(data->file, data);
	check_intro(data->file);
	copy_map(data->file, data);
	data->file = init;
	check_content(data->map, data);
}
