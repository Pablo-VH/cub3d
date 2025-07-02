/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:39:43 by pavicent          #+#    #+#             */
/*   Updated: 2025/06/25 13:39:44 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_path(char *path, char *to_take)
{
	//size_t	i;

	//i = 0;
	if (path)
		return ;
	/*while (to_take[i])
	{
		if (i >= 2 && to_take[i] && ft_isspace(to_take[i]))
			i++;
	}*/
	path = ft_strtrim_p(to_take, " \t\v\f\r\n");
}

void	ft_add_back(t_cub3D *data, char *line, int i)
{
	t_lines	*tmp;
	t_lines	*node;

	node = ft_alloc(sizeof(t_lines), 1);
	node->i = i;
	node->str = line;
	node->next = NULL;

	if (!data->file)
	{
		data->file = node;
		return ;
	}
	tmp = data->file;
	while (data->file->next)
		data->file = data->file->next;
	data->file->next = node;
	data->file = tmp;
}

void	check_file(char *av, t_cub3D *data)
{
	char	*line;
	int		i;

	data->fd = open(av, O_RDONLY);
	if (data->fd < 0)
		ft_perror_and_exit("Cub3d", 9);
	i = 1;
	while (1)
	{
		line = ft_strtrim_p(get_next_line_p(data->fd, 0), " \t\v\f\r");
		if (!line)
			break ;
		ft_add_back(data, line, i);
		i++;
	}
	get_next_line_p(-1, 1);
	close(data->fd);
}
