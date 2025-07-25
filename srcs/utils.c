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
	ft_printf("%d\n", data->fd);
	if (data->fd >= 0)
	{
		if (close(data->fd) < 0)
			ft_perror_and_exit("Cub3D: close", 28);
	}
	ft_alloc(0, 0);
	ft_print_message_and_exit(s, exit_key);
	exit(exit_key);
}

void	ft_terminate_mlx_and_exit(t_cub3D *data, int wd, char *s, int ext)
{
	if (data->canvas)
		mlx_delete_image(data->mlx, data->canvas);
	if (data->textures)
	{
		if (data->textures->n)
			mlx_delete_texture(data->textures->n);
		if (data->textures->s)
			mlx_delete_texture(data->textures->s);
		if (data->textures->e)
			mlx_delete_texture(data->textures->e);
		if (data->textures->w)
			mlx_delete_texture(data->textures->w);
	}
	if (wd)
	{
		mlx_close_hook(data->mlx, ft_hook, data);
		mlx_close_window(data->mlx);
	}
	mlx_terminate(data->mlx);
	ft_print_message_and_exit(s, ext);
}
