
#include "cub3D.h"

void	ft_print_message_and_exit(char *s, int exit_key)
{
	ft_dprintf(2, RED"Error\n%s\n"RESET, s);
	ft_alloc(0, 0);
	exit (exit_key);
}