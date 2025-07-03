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

/*void	get_path(char *path, char *to_take)
{
	//size_t	i;

	//i = 0;
	if (path)
		return ;
	while (to_take[i])
	{
		if (i >= 2 && to_take[i] && ft_isspace(to_take[i]))
			i++;
	}
	path = ft_strtrim_p(to_take, " \t\v\f\r\n");
}*/

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

int	count_elements(const int *elements)
{
	int	i;
	int	num_of_elements;

	i = 0;
	num_of_elements = 0;
	while (i < 6)
	{
		if (elements[i] > 1)
		{
			get_next_line_p(-1, 1);
			ft_print_message_and_exit("Repeated elements", 12);
		}
		num_of_elements += elements[i];
		i++;
	}
	return (num_of_elements);
}

int	check_line(char *line, t_cub3D *data)
{
	static int	elements[6];

	check_elements(line);
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
	if (count_elements(elements) == 6)
	{
		charge_info(data);
		return (1);
	}
	return (0);
}

void	check_file(char *av, t_cub3D *data)
{
	char	*line;
	int		i;

	data->fd = open(av, O_RDONLY);
	if (data->fd < 0)
		ft_perror_and_exit("Cub3d: open", 9);
	i = 1;
	while (1)
	{
		line = ft_strtrim_p(get_next_line_p(data->fd, 0), " \t\v\f\r\n");
		if (!line)
			ft_print_message_and_exit("Map not found", 13);
		ft_add_back(data, line, i);
		if (check_line(line, data))
		{
			printf("%s\n", data->p_no);
			printf("%s\n", data->p_so);
			printf("%s\n", data->p_we);
			printf("%s\n", data->p_ea);
			printf("%i\n",data->c_colours.r);
			printf("%i\n",data->c_colours.g);
			printf("%i\n",data->c_colours.b);
			printf("%i\n",data->f_colours.r);
			printf("%i\n",data->f_colours.g);
			printf("%i\n",data->f_colours.b);
			break ;
		}
		i++;
	}
	//copiar mapa
	get_next_line_p(-1, 1);
	close(data->fd);
}
