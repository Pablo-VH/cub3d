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

void	take_path(char *path, char *to_take)
{
	size_t	i;

	i = 0;
	if (path)
		return ;
	while (to_take[i])
	{
		if (i >= 2 && to_take[i] && ft_isspace(to_take[i]))
			i++;
	}
	path = ft_substr(to_take, i, ft_strlen(to_take) - i);
}

void	ft_add_back(t_cub3D *data, char *line, int i)
{
	t_lines	*tmp;
	t_lines	*new;

	tmp = data->file;
	if (!data->file)
	{
		data->file = ft_calloc(1, sizeof(data->file));
		data->file->i = i;
		data->file->str = line;
		data->file->next = NULL;
	}
	else
	{
		while (data->file->next)
			data->file = data->file->next;
		new = ft_calloc(1, sizeof(data->file));
		new->i = i;
		new->str = line;
		new->next = NULL;
		data->file->next = new;
	}
	data->file = tmp;
}

int	check_file(char *av, t_cub3D *data)
{
	char	*line;
	int		i;

	data->fd = open(av, O_RDONLY);
	i = 1;
	if (data->fd < 0)
	{
		perror("Cub3D: not such file or directory\n");
		exit (EXIT_FAILURE);
	}
	while (1)
	{
		line = get_next_line(data->fd);
		if (!line)
			break ;
		ft_add_back(data, line, i);
		i++;
	}
	close(data->fd);
}
