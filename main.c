#include "cub3d.h"

void	loop(t_game *game)
{
	mlx_loop_hook(game->mlx, ft_move_player, game);
	mlx_loop_hook(game->mlx, ft_move_arrow, game);
}

void ft_move_arrow(void* param)
{
	t_game	*game;

	game = (t_game *)param;

	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player->arrow_angle = game->player->arrow_angle - 10;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player->arrow_angle = game->player->arrow_angle + 10;

    mlx_delete_image(game->mlx, game->player->player_arrow);
	draw_arrow(game);
}

float	convert_degrees(float degree)
{
	float	radian;

	radian = (degree * (PI / 180));
	return (radian);
}

void	fill_arrow(t_game *game)
{
	int		i;
	int		center_pos;

	float	x_dir;
	float	y_dir;

	center_pos = 200;
	x_dir = cos(convert_degrees(game->player->arrow_angle));
	y_dir = sin(convert_degrees(game->player->arrow_angle));

	i = 0;
	while (i < ARROW_LENGTH)
	{
		mlx_put_pixel(game->player->player_arrow,
			center_pos + x_dir * i,
			center_pos + y_dir * i, 0xFC3503FF);
		i++;
	}
}

void	draw_arrow(t_game *game)
{
	game->player->player_arrow = mlx_new_image(game->mlx, 300, 300); // 200px width & height

	fill_arrow(game);

	mlx_image_to_window(game->mlx, game->player->player_arrow,
		game->player->x_position - 200 + PLAYER_SIZE / 2,
		game->player->y_position - 200 + PLAYER_SIZE / 2);
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


