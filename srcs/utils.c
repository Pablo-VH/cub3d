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

void	ft_print_message_and_exit(char *s, int exit_key)
{
	ft_dprintf(2, RED"Error\n%s\n"RESET, s);
	ft_alloc(0, 0);
	exit (exit_key);
}

void	ft_perror_and_exit(char *s, int exit_key)
{
	write(2, &RED, ft_strlen(RED));
	perror(s);
	write(2, &RESET, ft_strlen(RESET));
	ft_alloc(0, 0);
	exit (exit_key);
}