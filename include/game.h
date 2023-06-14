/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awis <awis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:45:28 by awis              #+#    #+#             */
/*   Updated: 2023/06/13 21:10:04 by awis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <mlx.h>
# include <stdio.h>
# include "ft_printf/include/ft_printf.h"
# include "ft_printf/include/libft.h"
# include "get_next_line/get_next_line.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define BLOCK_SIZE 70

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		steps;
}				t_game;

typedef struct s_sprites
{
	void	*hero;
	void	*floor;
	void	*collectible;
	void	*border;
	void	*exit;
}				t_sprites;

typedef struct s_coordinates
{
	int		x;
	int		y;
}				t_coordinates;

typedef struct s_map_data
{
	char	**map;
	int		map_width;
	int		map_height;
}				t_mapdata;

int				is_valid_char(char c);
char			**copy_map(char **map, int map_width, int map_height);
int				check_map_closed(char **map, int map_width, int map_height);
void			flood_fill(t_mapdata data, int x, int y);
void			free_map(char **map, int map_height);
int				check_map_path(char **map, int map_width, int map_height);
int				check_map_conditions(char **map, int map_width,
					int map_height, t_game *game);
int				get_line_width(char *line);
int				map_validate(int fd, t_game *game);
void			*load_sprite(void *mlx_ptr, char *filepath);
void			draw_block(t_game *game, void *sprite, int x, int y);
void			draw_map(t_game *game);
int				open_file(const char *filename);
void			draw_block_at_position(t_game *game,
					char block_type, int x, int y);
void			handle_movement(t_game *game, int new_x, int new_y);
int				key_press_handler(int keycode, t_game *game);
void			run_program(int fd);
void			draw_blocks(t_game *game, t_sprites *sprites);
void			draw_block_type(t_game *game, t_sprites *sprites,
					char block_type, t_coordinates coords);
int				validate_map_conditions(t_game *game);
int				validate_map(int fd, t_game *game, char *line);
int				validate_map_size(t_game *game);
int				validate_map_chars(t_game *game);
int				validate_map_closed(t_game *game);
int				print_error(char *msg);
void			update_coords(char **map, int *coords, int x, int y);
int				validate_conditions(int *coords);
int				check_unreachable_areas(char **map,
					int map_width, int map_height);
char			*copy_row(char *row, int row_width);
void			load_sprites(t_game *game, void **floor, void **hero);
int				check_boundaries(t_game *game, int new_x, int new_y);
int				check_wall(t_game *game, int new_x, int new_y);
void			handle_exit(t_game *game, int new_x, int new_y);
void			handle_collectible(t_game *game, int new_x, int new_y);
void			remove_old_player(t_game *game, void *floor);
void			update_position(t_game *game, int new_x, int new_y);
void			draw_new_player(t_game *game, void *hero);
int				close_handler(void *param);

#endif /* GAME_H */
