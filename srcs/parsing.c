/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:39:43 by pavicent          #+#    #+#             */
/*   Updated: 2025/06/25 13:39:44 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	charge_info(t_cub3D *data)
{
	while (data->file)
	{
		if (!ft_strncmp(data->file->content, "NO ", 3))
			charge_t_info(data->file->content, &data->p_no, "NO", data);
		if (!ft_strncmp(data->file->content, "SO ", 3))
			charge_t_info(data->file->content, &data->p_so, "SO", data);
		if (!ft_strncmp(data->file->content, "WE ", 3))
			charge_t_info(data->file->content, &data->p_we, "WE", data);
		if (!ft_strncmp(data->file->content, "EA ", 3))
			charge_t_info(data->file->content, &data->p_ea, "EA", data);
		if (!ft_strncmp(data->file->content, "F ", 2))
			charge_color_info(data->file->content, &data->f_colours, "F", data);
		if (!ft_strncmp(data->file->content, "C ", 2))
			charge_color_info(data->file->content, &data->c_colours, "C", data);
		data->file = data->file->next;
	}
}

static void	check_elements(char *line, t_cub3D *data)
{
	if (ft_strncmp(line, "C ", 2) && ft_strncmp(line, "F ", 2)
		&& ft_strncmp(line, "NO ", 3) && ft_strncmp(line, "SO ", 3)
		&& ft_strncmp(line, "WE ", 3) && ft_strncmp(line, "EA ", 3)
		&& ft_strncmp(line, "\0", 2))
		ft_close_fd_and_exit("Invalid line", 11, data);
}

static int	count_elements(const int *elements, t_cub3D *data)
{
	int	i;
	int	num_of_elements;

	i = 0;
	num_of_elements = 0;
	while (i < 6)
	{
		if (elements[i] > 1)
			ft_close_fd_and_exit("Repeated elements", 12, data);
		num_of_elements += elements[i];
		i++;
	}
	return (num_of_elements);
}

static int	check_line(char *line, t_cub3D *data)
{
	static int	elements[6];

	check_elements(line, data);
	if (!ft_strncmp(line, "NO ", 3))
		elements[0]++;
	if (!ft_strncmp(line, "SO ", 3))
		elements[1]++;
	if (!ft_strncmp(line, "WE ", 3))
		elements[2]++;
	if (!ft_strncmp(line, "EA ", 3))
		elements[3]++;
	if (!ft_strncmp(line, "F ", 2))
		elements[4]++;
	if (!ft_strncmp(line, "C ", 2))
		elements[5]++;
	if (count_elements(elements, data) == 6)
	{
		charge_info(data);
		return (1);
	}
	return (0);
}

void	parsing(char *av, t_cub3D *data)
{
	char	*line;
	t_list	*node;

	data->fd = open(av, O_RDONLY);
	if (data->fd < 0)
		ft_perror_and_exit("Cub3D: open", 9);
	while (1)
	{
		line = ft_strtrim_p(get_next_line_p(data->fd, 0), " \t\v\f\r\n");
		if (!line)
			ft_close_fd_and_exit("Map not found", 13, data);
		node = ft_lstnew_p(line);
		ft_lstadd_back(&data->file, node);
		if (check_line(line, data))
			break ;
	}
	line = get_next_line_p(data->fd, 0);
	while (*line == '\n')
	{
		line = get_next_line_p(data->fd, 0);
		if (!line)
			ft_close_fd_and_exit("Map not found", 19, data);
	}
	line = ft_strtrim_p(line, "\n");
	charge_map_lst(line, data);
}
