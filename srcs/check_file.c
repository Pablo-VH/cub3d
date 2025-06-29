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

#include "../inc/cub3D.h"

void	take_path(char *path, char *to_take)
{
	size_t	i;

	i = 0;
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
	t_lines	*tmp; //probablemente innecesario
	t_lines	*node;
	//t_lines	*new;

	node = ft_alloc(sizeof(t_lines), 1);
	node->i = i;
	node->str = line;
	node->next = NULL;

	if (!data->file)
	{
		data->file = node;
		return ;
	}
	tmp = data_file;//probablemente innecesario
	while (data->file->next)
		data->file = data->file->next;
	data->file->next = node;
	data->file = tmp;
	/*tmp = data->file;
	if (!data->file)
	{
		data->file = ft_alloc(sizeof(data->file), 1);
		data->file->i = i;
		data->file->str = line;
		data->file->next = NULL;
	}
	else
	{
		while (data->file->next)
			data->file = data->file->next;
		new = ft_alloc(sizeof(data->file), 1);
		new->i = i;
		new->str = line;
		new->next = NULL;
		data->file->next = new;
	}
	data->file = tmp;*/
}

int	check_file(char *av, t_cub3D *data)
{
	char	*line;
	int		i;

	data->fd = open(av, O_RDONLY);
	if (data->fd < 0)
	{
		perror("Cub3D: no such file or directory\n");
		ft_alloc(0, 0);
		exit (EXIT_FAILURE);
	}
	i = 1;
	while (1)
	{
		line = get_next_line_p(data->fd, 0);
		if (!line)
			break ;
		ft_add_back(data, line, i);
		i++;
	}
	get_next_line_p(-1, 1);
	close(data->fd);
}
