#include "cub3d.h"

int	is_wall(t_game *game, int new_x, int new_y)
{
	int	x;
	int	y;

	x = new_x / WALL_BLOCK_SIZE;
	y = new_y / WALL_BLOCK_SIZE;

	if (new_x < 0 || new_y < 0)
		return (1);

	if (game->data->grid[y] == NULL)
		return (1);

	if (x >= ft_strlen(game->data->grid[y]))
		return (1);

	if (game->data->grid[y][x] == '1')
		return (1);

	return (0);
}

void ft_move_player(void* param)
{
	t_game	*game;
	int		new_x;
	int		new_y;

	game = (t_game *)param;

	new_x = game->player->x_position;
	new_y = game->player->y_position;

	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		new_y -= SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		new_y += SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		new_x -= SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		new_x += SPEED;

	/*
	I should improve this so that it is checking all sides of the box. If  I  minus
	either the x or y by the plaer side I can  check  if  that  specific  point  is
	hitting a wall. But what is  the  current  default?  This  still  needs  to  be
	improved. But for now it is able to stop the player  moving  through  walls.  I
	will come back to this.
	*/
	if (is_wall(game, new_x, new_y) == 1
		|| is_wall(game, new_x, new_y + PLAYER_SIZE - 1) == 1
		|| is_wall(game, new_x + PLAYER_SIZE - 1, new_y) == 1
	)
	{
		game->player->player_image->instances[0].x = game->player->x_position;
		game->player->player_image->instances[0].y = game->player->y_position;
	}
	else
	{
		game->player->x_position = new_x;
		game->player->y_position = new_y;
		game->player->player_image->instances[0].x = new_x;
		game->player->player_image->instances[0].y = new_y;
	}
}

