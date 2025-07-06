/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-04 12:13:55 by dagimeno          #+#    #+#             */
/*   Updated: 2025-07-04 12:13:55 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_state(int prev, int pos)
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

static int	get_state(int prev, char c)
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

void	check_num(char **line, t_cub3D *data)
{
	int	state;

	state = 0;
	while (**line && **line != ',')
	{
		state = get_state(state, **line);
		if (state == 0)
			ft_close_fd_and_exit("Invalid rgb value", 17, data);
		(*line)++;
	}
	if (**line == ',')
		(*line)++;
}

static void	check_color_input_validity(t_rgb *colors, t_cub3D *data)
{
	if (colors->r < 0 || colors->r > 255
		|| colors->g < 0 || colors->g > 255
		|| colors->b < 0 || colors->b > 255)
		ft_close_fd_and_exit("Invalid rgb value", 20, data);
}

void	charge_color_data(int n, t_rgb *colors, char *line, t_cub3D *data)
{
	if (n == 1)
		colors->r = ft_atoi(ft_strtrim_p(line, " \t\v\f\r"));
	if (n == 2)
		colors->g = ft_atoi(ft_strtrim_p(line, " \t\v\f\r"));
	if (n == 3)
		colors->b = ft_atoi(ft_strtrim_p(line, " \t\v\f\r"));
	check_color_input_validity(colors, data);
}
