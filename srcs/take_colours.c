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

void	take_blue(char *colours, int i, t_cub3D *data, int flag)
{
	char	*tmp;
	int		j;

	if (data->err == true)
		return ;
	j = 0;
	tmp = ft_calloc(3 + 1, sizeof(char));
	while (colours[i] != ',')
	{
		tmp[j] = colours[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	if (flag == FLOOR)
		data->f_colours.b = ft_atoi(tmp);
	else
		data->c_colours.b = ft_atoi(tmp);
	free(tmp);
}

int	take_green(char *colours, int i, t_cub3D *data, int flag)
{
	char	*tmp;
	int		j;

	if (data->err == true)
		return (0);
	j = 0;
	tmp = ft_calloc(3 + 1, sizeof(char));
	while (colours[i] != ',')
	{
		tmp[j] = colours[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	if (flag == FLOOR)
		data->f_colours.r = ft_atoi(tmp);
	else
		data->c_colours.r = ft_atoi(tmp);
	free(tmp);
	return (i + 1);
}

int	take_red(char *colours, int i, t_cub3D *data, int flag)
{
	char	*tmp;
	int		j;

	if (data->err == true)
		return (0);
	j = 0;
	tmp = ft_calloc(3 + 1, sizeof(char));
	while (colours[i] != ',')
	{
		tmp[j] = colours[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	if (flag == FLOOR)
		data->f_colours.r = ft_atoi(tmp);
	else
		data->c_colours.r = ft_atoi(tmp);
	free(tmp);
	return (i + 1);
}

void	check_line(char *colours, int i, t_cub3D *data)
{
	int	j;

	j = 0;
	while (colours[i] && data->err == false)
	{
		while (ft_isdigit(colours[i]))
			i++;
		if (colours[i] && colours[i]  == ',')
		{
			i++;
			j++;
		}
		if (colours[i] && !ft_isdigit(colours[i]))
		{
			data->err = true;
			break ;
		}
	}
	if (j != 2)
		data->err = true;
}

void	take_fc(char *colours, t_cub3D *data, int flag)
{
	int	i;

	if (colours[2] && ft_isdigit(colours[2]))
	{
		check_line(colours, 2, data);
		i = take_red(colours, 2, data, flag);
		i = take_green(colours, i, data, flag);
		take_blue(colours, i, data, flag);
	}
	else
		data->err = true;
}
