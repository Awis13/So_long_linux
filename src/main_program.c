/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awis <awis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:15:58 by awis              #+#    #+#             */
/*   Updated: 2023/06/13 21:11:00 by awis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// This function runs the game.
// It takes the file descriptor of the game map file as a parameter.
// It validates the map, initializes the game state, 
// creates a new window, draws the map, and starts the game loop.
void	run_program(int fd)
{
	t_game	game;

	game = (t_game){0};
	if (!map_validate(fd, &game))
		return ;
	close(fd);
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, game.map_width
			* BLOCK_SIZE, game.map_height * BLOCK_SIZE, "So_long!");
	draw_map(&game);
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press_handler, &game);
	mlx_hook(game.win_ptr, 17, 1L << 17, close_handler, NULL);
	mlx_loop(game.mlx_ptr);
}

// This function draws all the blocks in the game map.
// It takes a pointer to the game state 
// and a pointer to the sprites as parameters.
// It iterates over the game map and draws the 
// corresponding block for each character.
void	draw_blocks(t_game *game, t_sprites *sprites)
{
	t_coordinates	coords;
	char			block_type;

	coords.y = 0;
	while (coords.y < game->map_height)
	{
		coords.x = 0;
		while (coords.x < game->map_width)
		{
			block_type = game->map[coords.y][coords.x];
			draw_block_type(game, sprites, block_type, coords);
			coords.x++;
		}
		coords.y++;
	}
}

// This function draws a specific type of block on the game map.
// It takes a pointer to the game state, a pointer to the sprites, 
// the type of block to draw, and the coordinates as parameters.
// Depending on the block type, it draws 
// the corresponding sprite at the given coordinates.
// If the block type is a player, it also updates the 
// player coordinates in the game state.
void	draw_block_type(t_game *game, t_sprites *sprites,
		char block_type, t_coordinates coords)
{
	if (block_type == 'E')
		draw_block(game, sprites->exit, coords.x, coords.y);
	else if (block_type == '1')
		draw_block(game, sprites->border, coords.x, coords.y);
	else if (block_type == '0')
		draw_block(game, sprites->floor, coords.x, coords.y);
	else if (block_type == 'C')
		draw_block(game, sprites->collectible, coords.x, coords.y);
	else if (block_type == 'P')
	{
		draw_block(game, sprites->hero, coords.x, coords.y);
		game->player_x = coords.x;
		game->player_y = coords.y;
	}
	else
	{
	}
}

// This function validates the conditions of the game map.
// It takes a pointer to the game state as a parameter.
// It checks if the map conditions 
// are met and returns 1 if they are not and 0 if they are.
int	validate_map_conditions(t_game *game)
{
	if (!check_map_conditions(game->map, game->map_width,
			game->map_height, game))
		return (1);
	return (0);
}
