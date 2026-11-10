#include "cub3d.h"

#define PI 3.14159265358979323846

/*
	• (X) Coordinate: Radius x cos(Radians)
	• (Y) Coordinate: Radius x sin(Radians)

double degrees = 90.0;
double radius = 10.0; // Distance from the center poin

What is a Radian?

// Convert to radians inside the function call: degrees * (PI / 180.0)
double x = radius * cos(degrees * (PI / 180.0));
double y = radius * sin(degrees * (PI / 180.0));

*/

void	loop(t_game *game)
{
	mlx_loop_hook(game->mlx, ft_move_player, game);
	mlx_loop_hook(game->mlx, ft_move_arrow, game);
}

/*
::::::::::::::::::::::::::		THINKING	   ::::::::::::::::::::::::::::::::::::

The hardest number to find is the exact x and y positions that the mlx_put_pixel()
can use. To find these numbers I have to understand sin and cos. These two maths
functions return the number values I need so that mlx_put_pixel() can accuratly put
the pixel in the correct position and draw the line.

To get the correct value I need to do a calculation.

I need to times the degrees, say 90

f

*/

void ft_move_arrow(void* param)
{
	t_game	*game;

	game = (t_game *)param;

	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player->direction_x = game->player->direction_x - 0.3;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player->direction_x = game->player->direction_y + 0.3;

    mlx_delete_image(game->mlx, game->player->player_arrow);

	draw_arrow(game);

}

void	fill_arrow(t_game *game)
{
	int		i;
	float	dir_x;
	float	dir_y;
	float	pos_x;
	float	pos_y;

	dir_x = game->player->direction_x;
	dir_y = game->player->direction_y;

	pos_x =  200;
	pos_y =  100;

	i = 0;
	while (i < 100)
	{
		mlx_put_pixel(game->player->player_arrow, pos_x, pos_y, 0xF5291BFF);
		pos_x = pos_x + dir_x;
		pos_y = pos_y + dir_y;
		i++;
	}
}

void	draw_arrow(t_game *game)
{
	game->player->player_arrow = mlx_new_image(game->mlx, 200, 200); // 200px width & height

	fill_arrow(game);

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


