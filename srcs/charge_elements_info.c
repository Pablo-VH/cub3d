#include "cub3D.h"

void	check_and_charge_wall_info(char *line, char **recipient, char *beginning)
{
	line = ft_strtrim_p(line, beginning);
	while (ft_isspace(*line))
		line++;
	if (!*line || ft_strchr(line, ' ') || ft_strchr(line, '\t')
		|| ft_strchr(line, '\n') || ft_strchr(line, '\v')
		|| ft_strchr(line, '\f') || ft_strchr(line, '\r'))
	{
		get_next_line_p(-1, 1);
		ft_print_message_and_exit("Invalid wall texture", 14);
	}
	*recipient = line;
}

void	check_character_validity(char *line)
{
	if ((*line != '+' && !ft_isdigit(*line))
		|| (*line == '+' && (*(line + 1) == '\0'))
		|| (*line == '+' && *(line + 1) && !ft_isdigit(*(line + 1))))
	{
		get_next_line_p(-1, 1);
		ft_print_message_and_exit("Invalid rgb colors", 16);
	}
}

void	check_and_charge_color_info(char *line, t_rgb *colors, char *beginning)
{
	int	num_of_colors;

	line = ft_strtrim_p(line, beginning);
	num_of_colors = 0;
	while (*line)
	{
		while(ft_isspace(*line))
			line++;
		check_character_validity(line);
		num_of_colors++;
		if (num_of_colors > 3)
			break ;
		charge_color_data(num_of_colors, colors, line);
		while (*line && *line != ',')
		{
			//check_character_validity(line);
			check_num(&line);
		}
		line++;
	}
	if (num_of_colors != 3 )
	{
		get_next_line_p(-1, 1);
		ft_print_message_and_exit("Invalid rgb colors", 17);
	}
}

void	charge_info(t_cub3D *data)
{
	while (data->file)
	{
		if (!ft_strncmp(data->file->str, "NO ", 3))
			check_and_charge_wall_info(data->file->str, &data->p_no, "NO");
		if (!ft_strncmp(data->file->str, "SO ", 3))
			check_and_charge_wall_info(data->file->str, &data->p_so, "SO");
		if (!ft_strncmp(data->file->str, "WE ", 3))
			check_and_charge_wall_info(data->file->str, &data->p_we, "WE");
		if (!ft_strncmp(data->file->str, "EA ", 3))
			check_and_charge_wall_info(data->file->str, &data->p_ea, "EA");
		if (!ft_strncmp(data->file->str, "F ", 2))
			check_and_charge_color_info(data->file->str, &data->f_colours, "F");
		if (!ft_strncmp(data->file->str, "C ", 2))
			check_and_charge_color_info(data->file->str, &data->c_colours, "C");
		data->file = data->file->next;
	}
}
