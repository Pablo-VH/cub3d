/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:59:54 by pavicent          #+#    #+#             */
/*   Updated: 2025/07/02 20:59:58 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_state(int prev, int pos)
{
	static int	state[][4] = {
	{N_ERR, N_NUM, N_SYM, N_SPA},
	{N_ERR, N_NUM, N_SP2, N_ERR},
	{N_ERR, N_NUM, N_SYM, N_SPA},
	{N_ERR, N_NUM, N_ERR, N_ERR},
	{N_ERR, N_ERR, N_SP2, N_ERR}
	};

	return (state[prev][pos]);
}

int	get_state(int prev, char c)
{
	int	current;

	current = 0;
	if (ft_isdigit(c))
		current = 1;
	else if (ft_isspace(c))
		current = 2;
	else if (c == '-' || c == '+')
		current = 3;
	return (check_state(prev, current));
}

void	check_num(char **line)
{
	int		state;

	state = 0;
	while (**line && **line != ',')
	{
		state = get_state(state, **line);
		if (state == 0)
			ft_print_message_and_exit("Invalid rgb number", 7);
		(*line)++;
	}
	if (**line == ',')
		(*line)++;
}

/*
void	check_colors(t_cub3D *data)
{
	printf("c.r = %i\n", data->c_colours.r);
	printf("c.g = %i\n", data->c_colours.g);
	printf("c.b = %i\n", data->c_colours.b);
	printf("f.r = %i\n", data->f_colours.r);
	printf("f.g = %i\n", data->f_colours.g);
	printf("f.b = %i\n", data->f_colours.b);
	if (data->c_colours.r < 0 || data->c_colours.r > 255
		|| data->c_colours.g < 0 || data->c_colours.g > 255
		|| data->c_colours.b < 0 || data->c_colours.b > 255
		|| data->f_colours.r < 0 || data->f_colours.r > 255
		|| data->f_colours.g < 0 || data->f_colours.g > 255
		|| data->f_colours.b < 0 || data->f_colours.b > 255)
		ft_print_message_and_exit("Invalid color value", 6);
}*/

void	check_color_input_validity(t_rgb *colors)
{
	if (colors->r < 0 || colors->r > 255
		|| colors->g < 0 || colors->g > 255
		|| colors->b < 0 || colors->b > 255)
	{
		get_next_line_p(-1, 1);
		ft_print_message_and_exit("Invalid rgb number", 17);
	}
}

void	charge_color_data(int num_of_colors, t_rgb *colors, char *line)
{
	if (num_of_colors == 1)
		colors->r = ft_atoi(ft_strtrim_p(line, " \t\v\f\r"));
	if (num_of_colors == 2)
		colors->g = ft_atoi(ft_strtrim_p(line, " \t\v\f\r"));
	if (num_of_colors == 3)
		colors->b = ft_atoi(ft_strtrim_p(line, " \t\v\f\r"));
	check_color_input_validity(colors);
}
