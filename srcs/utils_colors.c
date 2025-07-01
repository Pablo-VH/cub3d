#include "cub3D.h"

int	check_state(int prev, int pos)
{
	int state[][4] ={
		{N_ERR, N_NUM, N_SYM, N_SPA}, //INI prev = 0
		{N_ERR, N_NUM, N_ERR, N_ERR}, //ISDIGIT prev = 1
		{N_ERR, N_NUM, N_SYM, N_SPA}, //ISSPACE prev = 2
		{N_ERR, N_NUM, N_ERR, N_ERR} 
	};
	return (state[prev][pos]);
}

int	take_state(int prev, char c)
{
	int	now;

	now = 0;
	if (ft_isdigit(c))
		now = 1;
	else if (ft_isspace(c))
		now = 2;
	else if (c == '-' || c == '+')
		now = 3;
	return (check_state(prev, now));
}

void	check_num(char *str)
{
	int	i;
	int	state;

	i = 0;
	state = 0;
	while (str[i] && str[i] != '\n')
	{
		state = take_state(state, str[i]);
		if (state == 0)
			ft_print_message_and_exit("Invalid number", 7);
		i++;
	}
	if (state == 2)
		ft_print_message_and_exit("Number missing", 7);
}

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
}
