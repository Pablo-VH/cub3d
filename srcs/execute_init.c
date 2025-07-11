#include "cub3D.h"

static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	(void)mlx;
	//printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

int	execute_game(t_cub3D *data)
{
	(void)data;
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_texture_t	*texture;
	mlx = mlx_init(1920, 1080, "42Cub3D", true);
	if (!mlx)
		ft_print_message_and_exit("Error with mlx", 30);
	texture = mlx_load_png("/home/pavicent/Downloads/lama.png");
	img = mlx_texture_to_image(mlx, texture);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_print_message_and_exit("Error with img", 30);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_delete_texture(texture);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
