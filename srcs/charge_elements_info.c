#include "cub3D.h"

void	charge_t_info(char *line, char **recipient, char *def, t_cub3D *data)
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
	if (num_of_colors != 3)
		ft_close_fd_and_exit("Invalid number of colors", 15, data);
}

static void	charge_map_arr(t_cub3D *data, int size, int len)
{
	int		i;
	t_list	*map;

	data->map_arr = ft_alloc((size + 1) * sizeof(char *), 1);
	map = data->map_lst;
	i = 0;
	while (map)
	{
		data->map_arr[i] = ft_alloc(sizeof(char) * (len + 1), 1);
		ft_strlcpy(data->map_arr[i], map->content, len + 1);
		i++;
		map = map->next;
	}
	ft_check_walls(data->map_arr, size);
}

void	charge_map_lst(char *line, t_cub3D *data)
{
	t_list	*node;
	int		num_of_players;
	size_t	longest_line;

	num_of_players = 0;
	longest_line = 0;
	while (line)
	{
		node = ft_lstnew_p(line);
		ft_lstadd_back(&data->map_lst, node);
		if (*line == '\0')
			ft_close_fd_and_exit("Empty line found in map", 22, data);
		if (ft_are_invalid_characters(line, "01NSEW2 "))
			ft_close_fd_and_exit("Invalid character found in map", 21, data);
		ft_check_num_of_playrs(line, &num_of_players, data);
		if (longest_line < ft_strlen(line))
			longest_line = ft_strlen(line);
		line = ft_strtrim_p(get_next_line_p(data->fd, 0), "\n");
	}
	if (num_of_players == 0)
		ft_close_fd_and_exit("No player found", 24, data);
	get_next_line_p(-1, 1);
	close(data->fd);
	charge_map_arr(data, ft_lstsize(data->map_lst), longest_line);
}
