#include "cub3d.h"

void	loop(t_game *game)
{
	mlx_loop_hook(game->mlx, ft_move_player, game);
}


void	fill_arrow(t_game *game)
{
	int		i;
	float	dir_x;
	float	dir_y;
	float	pos_x;
	float	pos_y;

	// There must be 

	dir_x = game->player->direction_x;
	dir_y = game->player->direction_y;

	pos_x = game->player->x_position;
	pos_y = game->player->y_position;

	i = 0;
	while (i < 88) // 100 pixels long arrow
	{
		// Theres a segmentation fault here. Its not able to put the pixels at those positions
		// Currently pos_x = 858
		// Currently pos_y = 363
		// Why is this the case?
		mlx_put_pixel(game->player->player_arrow, pos_x, pos_y, 0x32A852FF);
		pos_x = pos_x + dir_x;
		pos_y = pos_y + dir_y;
		i++;
	}
}

void	draw_arrow(t_game *game)
{
	// At this point we have a square to work with. An "image" 
	game->player->player_arrow = mlx_new_image(game->mlx, 200, 200); // 200px width & height  

	// Now the square should be filled with a line that has the correct direction
	fill_arrow(game); 

	// Now I am putting the image in the window at the following coordinates. Should be above the player
	mlx_image_to_window(game->mlx, game->player->player_arrow, game->player->x_position, game->player->y_position);
}


int	main(int argc, char **argv)
{
	t_game	game;

	check_args(argc);

	init(&game, argv[1]);

	draw_mini_map(&game);

	draw_player(&game);

	draw_arrow(&game);

	loop(&game);

	mlx_loop(game.mlx);

	mlx_terminate(game.mlx);

	return (1);
}


