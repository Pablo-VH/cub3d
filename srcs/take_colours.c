/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_colours.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:19:06 by pavicent          #+#    #+#             */
/*   Updated: 2025/06/26 10:19:08 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		take_len(char *colours, int i, t_cub3D *data)
{
	int	init;

	while (colours[i] && ft_isspace(colours[i]))
		i++;
	init = i;
	while (colours[i] && colours[i] != ',' && colours[i] !='\n')
		i++;
	if (colours[i] && !ft_isspace(colours[i]) && colours[i] != ',' 
		&& i - init <= 0 && i - init > 3)
	{
		data->err = true;
		return (0);
	}
	return  (i - init);
}

void	take_blue(char *colours, int i, t_cub3D *data, int flag)
{
	char	*tmp;
	int		j;
	int		len;

	j = 0;
	len = take_len(colours, i, data);
	tmp = ft_alloc((len + 1) * sizeof(char), 1);
	if (len != 0)
	{
		while (colours[i] && len != 0)
		{
			tmp[j] = colours[i];
			i++;
			j++;
		}
		tmp[j] = '\0';
		check_num(tmp);
		if (flag == FLOOR)
			data->f_colours.b = ft_atoi(tmp);
		else
			data->c_colours.b = ft_atoi(tmp);
	}
}

int	take_green(char *colours, int i, t_cub3D *data, int flag)
{
	char	*tmp;
	int		j;
	int		len;

	j = 0;
	len = take_len(colours, i, data);
	tmp = ft_alloc((len + 1) * sizeof(char), 1);
	if (len != 0)
	{
		while (colours[i] != ',' && len != 0)
		{
			tmp[j] = colours[i];
			i++;
			j++;
		}
		tmp[j] = '\0';
		check_num(tmp);
		if (flag == FLOOR)
			data->f_colours.g = ft_atoi(tmp);
		else
			data->c_colours.g = ft_atoi(tmp);
	}
	return (i + 1);
}

int	take_red(char *colours, int i, t_cub3D *data, int flag)
{
	char	*tmp;
	int		j;
	int		len;

	j = 0;
	len = take_len(colours, i, data);
	tmp = ft_alloc((len + 1) * sizeof(char), 1);
	if (len != 0)
	{
		while (colours[i] != ',' && len != 0)
		{
			tmp[j] = colours[i];
			i++;
			j++;
		}
		tmp[j] = '\0';
		check_num(tmp);
		if (flag == FLOOR)
			data->f_colours.r = ft_atoi(tmp);
		else
			data->c_colours.r = ft_atoi(tmp);
	}
	return (len + 1);
}

int	iter_colours(char *colours, int i)
{
	while (colours[i] && ft_isspace(colours[i]) && colours[i] != '\n')
		i++;
	while (colours[i] && ft_isdigit(colours[i]))
		i++;
	while (colours[i] && ft_isspace(colours[i]) && colours[i] != '\n')
		i++;
	return (i);
}

void	check_line(char *colours, int i)
{
	int	j;

	j = 0;
	while (colours[i])
	{
		i = iter_colours(colours, i);
		if (colours[i] && colours[i]  == ',')
		{
			i++;
			j++;
		}
		if (colours[i - 1] == ',' && !colours[i])
			ft_print_message_and_exit("Number missing", 8);
	}
	if (j != 2)
		ft_print_message_and_exit("Number missing", 8);
}

void	take_fc(char *colours, t_cub3D *data, int flag)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strtrim_p(colours, " \n\t\v\r\fFC");
	printf("%s\n", tmp);
	if (tmp && tmp[i] && ft_isdigit(tmp[i]))
	{
		check_line(tmp, 0);
		i = take_red(tmp, 0, data, flag);
		i = take_green(tmp, i, data, flag);
		take_blue(tmp, i, data, flag);
	}
	else
		ft_print_message_and_exit("Colors not included", 5);
}
