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
	while (colours[i] && colours[i] != ',' && colours[i] !='\n'
			&& ft_isdigit(colours[i]))
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

	if (data->err == true)
		return (0);
	j = 0;
	len = take_len(colours, i, data);
	tmp = ft_calloc(len + 1, sizeof(char));
	if (len != 0)
	{
		while (colours[i] && len != 0)
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
	}
	free(tmp);
}

int	take_green(char *colours, int i, t_cub3D *data, int flag)
{
	char	*tmp;
	int		j;
	int		len;

	if (data->err == true)
		return (0);
	j = 0;
	len = take_len(colours, i, data);
	tmp = ft_calloc(len + 1, sizeof(char));
	if (len != 0)
	{
		while (colours[i] != ',' && len != 0)
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
	}
	free(tmp);
	return (len + 1);
}

int	take_red(char *colours, int i, t_cub3D *data, int flag)
{
	char	*tmp;
	int		j;
	int		len;

	if (data->err == true)
		return (0);
	j = 0;
	len = take_len(colours, i, data);
	tmp = ft_calloc(len + 1, sizeof(char));
	if (len != 0)
	{
		while (colours[i] != ',' && len != 0)
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
	}
	free(tmp);
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

void	check_line(char *colours, int i, t_cub3D *data)
{
	int	j;

	j = 0;
	while (colours[i] && data->err == false)
	{
		i = iter_colours(colours, i);
		if (colours[i] && ft_isdigit(colours[i]))
		{
			data->err = true;
			break ;
		}
		if (colours[i] && colours[i]  == ',')
		{
			i++;
			j++;
		}
		if ((colours[i] && !ft_isspace(colours[i]) && !ft_isdigit(colours[i]))
			|| (!colours[i] && colours[i - 1] == ','))
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
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strtrim_p(colours, " \n\t\v\r\fFC");
	if (tmp && tmp[i] && ft_isdigit(tmp[i]))
	{
		check_line(tmp, 0, data);
		i = take_red(colours, 0, data, flag);
		i = take_green(colours, i, data, flag);
		take_blue(colours, i, data, flag);
	}
	else
		data->err = true;
}
