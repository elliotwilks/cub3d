#include "cub3d.h"


/*
I need to be able to draw a line that shoots out in front of the player so I can
see the orientation of the player and when they rotate.

Common Pattern
Create the "new_image"
Fill the new_image;
Put the new_image to the screen

*/
void	ft_rotate_player(void *param)
{
	(void)param;
	/*
	int		x_oreintation;
	int		x_oreintation;
	t_game	*game;

	game = (t_game *)param;

	game->player->player_arrow = mlx_new_image(game->mlx, ARROW_WIDTH, ARROW_HEIGHT);

	draw_arrow(game->player->player_arrow);

	// How to fint the orientation?
	// How to rotate the image?

	mlx_image_to_window(game->mlx, game->player->player_arrow, )
	*/

}


void	loop(t_game *game)
{
	mlx_loop_hook(game->mlx, ft_move_player, game);
	mlx_loop_hook(game->mlx, ft_rotate_player, game);
}


int	main(int argc, char **argv)
{
	t_game	game;

	check_args(argc);

	init(&game, argv[1]);

	draw_mini_map(&game);

	draw_player(&game);

	loop(&game);

	mlx_loop(game.mlx);

	mlx_terminate(game.mlx);

	return (1);
}


