# ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include "MLX42.h"
#include "MLX42_Int.h"

#define WIDTH 1300
#define HEIGHT 900
#define BUFFER_SIZE 33
#define FIELD_OF_VIEW 60
#define HALF_FIELD_OF_VIEW 30
#define PLAYER_SIZE 27
#define ARROW_WIDTH 10
#define ARROW_HEIGHT 30
#define WALL_BLOCK_SIZE 33
#define SPEED 5

typedef struct s_data t_data;
typedef struct s_player t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	t_player	*player;
	t_data		*data;
}
t_game;

typedef struct s_data
{
	char	**grid;
	int		grid_x_max;	// x axis for left and right
	int		grid_y_max; // y axis for up and down
	int		line_count;

	char	*north_texture;
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;

	char	*floor;
	char	*ceiling;

	mlx_image_t		*wall;
}
t_data;

typedef struct s_player
{
	float			x_position;
	float			y_position;
	float			x_orientation; // x <--- Left and right
	float			y_orientation; // y <-- Up and down

	float			direction_x;
	float			direction_y;
	int				walk_direction;
	int				move_speed;
	int				rotation_speed;
	mlx_image_t		*player_image;
	mlx_image_t		*player_arrow;
}
t_player;


/*:::::::::::::::::::		UTLIS		:::::::::::::::::::::*/

int		ft_atoi(const char *str);
void	draw_in_image(void *param);
void	fill_square(void *param, uint32_t colour);
int		file_incorrect(char *path);
void	handle_error(void);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	custom_print(char *str);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s);
void	ft_putstr(char *str);
int		ft_strchr(char *str, char c);
char	*ft_strjoin(const char *s1, const char *s2);
char	*read_file(int fd, char *storage);
char	*extract_line(char *storage);
char	*update_storage(char *storage, char *line);
char	*get_next_line(int fd);
char	*ft_strtrim(char const *s1, char const *set);
int		is_set(char c, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
//void	print_grid(t_data *data);
void	check_args(int argc);

/*:::::::::::::::::::		PARSE		:::::::::::::::::::::*/

int		get_textures(t_data *data, char *path);
char	**get_grid(t_data *data, char *path, int fd_parsed);
int		count_lines(int fd);
t_data	*get_data(t_data *data, char *path);


/*:::::::::::::::::::		OTHERS		:::::::::::::::::::::*/

t_player	*build_player(t_game *game);
void		get_position(t_player *player, char **grid);
void		print_player(t_player *player);
void		init(t_game *game, char *argv);
void		print_grid(char **grid);


/*:::::::::::::::::::		LOOP FUNCTIONS		:::::::::::::::::::::*/

void	ft_move_player(void* param);
int		is_wall(t_game *game, int new_x, int new_y);


/*:::::::::::::::::::		DRAW FUNCTIONS		:::::::::::::::::::::*/

void		fill(mlx_image_t *img, uint32_t color);
void		draw_mini_map(t_game *game);
void		draw_player(t_game *game);


#endif //CUB3D_H
