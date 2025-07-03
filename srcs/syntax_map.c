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

void	copy_map(char *line, t_cub3D *data)
{
	t_list	*node;
	char	*content;

	content = ft_strdup_p(line);
	node = ft_lstnew_p(content);
	ft_lstadd_back(&data->map, node);
}
