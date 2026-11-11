#include "cub3d.h"

#define PI 3.14159265358979323846

/*
	• (X) Coordinate: Radius x cos(Radians)
	• (Y) Coordinate: Radius x sin(Radians)

double degrees = 90.0;
double radius = 10.0; // Distance from the center poin

What is a Radian?

Convert to radians inside the function call: degrees * (PI / 180.0)
double x = radius * cos(degrees * (PI / 180.0));
double y = radius * sin(degrees * (PI / 180.0));


x = radius * cos(radian value);

	 ^^^
  why radius? Ahh yes, the radius is just the distance out that we are going. 
  so in a while loop it usually will be i++. However I could call the variable
  radius++

  so as we increment radius by 1 each time. we also get a new x / y value beacuse
  we times the 1 or 2 or 3 or 4 by the return value of cos() or sin(). 

  The return value of cos() for example gives use the exact coordinate we need. 

  The cos(radian) function returns a value between -1 and 1. 
  The sin(radian) function does the same thing but is specific for the y cooridnates.

Finally this is beggining to click. 

I could make a special function that allowed me to simply pass the degree value I
want instead of having to pass the radian value. So I could do something like this

	 x = degree_cos(90); <--- Would return 0 
	 y = degree_sin(90); <--- Would return 1

	x_coordinate = x * radius;
	y_coordinate = y * radius;

So I should be able to take the return values of these funtions and give them 
to the mlx_put_pixel() function for the x and y coordinates for that specific
pixel and then increment the radius.

Then if I want to change the angle of the line with the arrow keys I shold be able
to increase or reduce the degree angle. Then remember to update the mlx image; 


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

Question: Why is any of this triginomitary stuff relevent to me?

I need to draw a line. This is easy. I can just use a while loop like this

while (i < 100)
{
	mlx_put_pixel(mlx, i, j, colour);
	i++;	
}

But if I want to draw a line that is at a certain degree from a single point

I need some x and y coordinates plus an angle?

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


