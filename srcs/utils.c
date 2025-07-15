/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42madrid>       #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-02 19:00:57 by dagimeno          #+#    #+#             */
/*   Updated: 2025-07-02 19:00:57 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_perror_and_exit(char *s, int exit_key)
{
	ft_alloc(0, 0);
	if (write(2, &RED, ft_strlen(RED)) < 0)
	{
		perror("cub3D: write");
		exit(29);
	}
	perror(s);
	if (write(2, &RESET, ft_strlen(RESET)) < 0)
	{
		perror("cub3D: write");
		exit(30);
	}
	exit (exit_key);
}

void	ft_print_message_and_exit(char *s, int exit_key)
{
	if (ft_dprintf(2, RED"Error\n%s\n"RESET, s) < 0)
		ft_perror_and_exit("cub3D: ft_dprintf", 31);
	ft_alloc(0, 0);
	exit (exit_key);
}

void	ft_close_fd_and_exit(char *s, int exit_key, t_cub3D *data)
{
	get_next_line_p(-1, 1);
	if (data->fd >= 0)
	{
		if (close(data->fd) < 0)
			ft_perror_and_exit("Cub3D: close", 28);
	}
	ft_alloc(0, 0);
	ft_print_message_and_exit(s, exit_key);
	exit(exit_key);
}
