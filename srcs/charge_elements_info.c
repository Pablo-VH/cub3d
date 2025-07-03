#include "cub3D.h"

void	check_and_charge_wall_info(char *line, char **recipient, char *def)
{
	line = ft_strtrim_p(line, def);
	while (ft_isspace(*line))
		line++;
	if (!*line || ft_strchr(line, ' ') || ft_strchr(line, '\t')
		|| ft_strchr(line, '\n') || ft_strchr(line, '\v')
		|| ft_strchr(line, '\f') || ft_strchr(line, '\r'))
	{
		get_next_line_p(-1, 1);
		ft_print_message_and_exit("Invalid wall texture", 14);
	}
	*recipient = ft_strdup_p(line);
}

void	check_and_charge_color_info(char *line, t_rgb *colors, char *def)
{
	int		num_of_colors;
	char	*beginning;

	line = ft_strtrim_p(line, def);
	num_of_colors = 0;
	while (*line)
	{
		beginning = line;
		check_num(&line);
		num_of_colors++;
		if (num_of_colors > 3)
			break ;
		charge_color_data(num_of_colors, colors, beginning);
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
