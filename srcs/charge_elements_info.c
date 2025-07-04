#include "cub3D.h"

void	charge_wall_info(char *line, char **recipient, char *def, t_cub3D *data)
{
	line = ft_strtrim_p(line, def);
	while (ft_isspace(*line))
		line++;
	if (!*line || ft_strchr(line, ' ') || ft_strchr(line, '\t')
		|| ft_strchr(line, '\n') || ft_strchr(line, '\v')
		|| ft_strchr(line, '\f') || ft_strchr(line, '\r'))
	ft_close_fd_and_exit("Invalid wall texture", 14, data);
	*recipient = line;
}

void	charge_color_info(char *line, t_rgb *colors, char *def, t_cub3D *data)
{
	int		num_of_colors;
	char	*beginning;

	line = ft_strtrim_p(line, def);
	num_of_colors = 0;
	while (*line)
	{
		beginning = line;
		check_num(&line, data);
		num_of_colors++;
		if (num_of_colors > 3)
			break ;
		charge_color_data(num_of_colors, colors, beginning, data);
	}
	if (num_of_colors != 3 )
		ft_close_fd_and_exit("Invalid number of colors", 15, data);
}

void	charge_info(t_cub3D *data)
{
	while (data->file)
	{
		if (!ft_strncmp(data->file->str, "NO ", 3))
			charge_wall_info(data->file->str, &data->p_no, "NO", data);
		if (!ft_strncmp(data->file->str, "SO ", 3))
			charge_wall_info(data->file->str, &data->p_so, "SO", data);
		if (!ft_strncmp(data->file->str, "WE ", 3))
			charge_wall_info(data->file->str, &data->p_we, "WE", data);
		if (!ft_strncmp(data->file->str, "EA ", 3))
			charge_wall_info(data->file->str, &data->p_ea, "EA", data);
		if (!ft_strncmp(data->file->str, "F ", 2))
			charge_color_info(data->file->str, &data->f_colours, "F", data);
		if (!ft_strncmp(data->file->str, "C ", 2))
			charge_color_info(data->file->str, &data->c_colours, "C", data);
		data->file = data->file->next;
	}
}
