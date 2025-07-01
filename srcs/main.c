/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:20:32 by pavicent          #+#    #+#             */
/*   Updated: 2025/06/24 19:20:34 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_cub3D	*data;

	if (ac != 2)
		ft_print_message_and_exit("Too many or no arguments", 1);
	if (!ft_check_extention(av[1], ".cub"))
		ft_print_message_and_exit("Not valid .cub extention", 1);
	data = ft_alloc(sizeof(t_cub3D), 1);
	check_map(av[1], data);
	ft_alloc(0, 0);
}
