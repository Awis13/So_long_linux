/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awis <awis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:15:23 by awis              #+#    #+#             */
/*   Updated: 2023/06/13 19:56:00 by awis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// This function opens a file for reading.
// It takes the filename as a parameter and returns the file descriptor.
// If the file cannot be opened, it prints an error message and returns -1.
int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	return (fd);
}

// This function draws a block at a given position in the game.
// It takes a pointer to the game state, the type of block to draw, 
// and the x and y coordinates as parameters.
// Depending on the block type, it loads the corresponding
// sprite and draws it at the given position.
void	draw_block_at_position(t_game *game, char block_type, int x, int y)
{
	void	*sprite;

	if (block_type == 'E')
		sprite = load_sprite(game->mlx_ptr, "textures/exit.xpm");
	else if (block_type == '1')
		sprite = load_sprite(game->mlx_ptr, "textures/border.xpm");
	else if (block_type == '0')
		sprite = load_sprite(game->mlx_ptr, "textures/floor.xpm");
	else if (block_type == 'C')
		sprite = load_sprite(game->mlx_ptr, "textures/collectible.xpm");
	else if (block_type == 'P')
		sprite = load_sprite(game->mlx_ptr, "textures/hero.xpm");
	else
		return ;
	draw_block(game, sprite, x, y);
}
// This function handles the movement of the player.
// It takes a pointer to the game state and the new x 
// and y coordinates as parameters.
// It checks if the movement is valid and updates the game state accordingly.
// If the player moves to the exit without collecting all collectibles, 
// it prints a message and does not move the player.

void	handle_movement(t_game *game, int new_x, int new_y)
{
	void	*floor;
	void	*hero;

	load_sprites(game, &floor, &hero);
	if (!check_boundaries(game, new_x, new_y))
		return ;
	if (!check_wall(game, new_x, new_y))
		return ;
	if (game->map[new_y][new_x] == 'E' && game->collectibles > 0)
	{
		printf("You must collect all collectibles before exiting.\n");
		return ;
	}
	handle_exit(game, new_x, new_y);
	handle_collectible(game, new_x, new_y);
	remove_old_player(game, floor);
	update_position(game, new_x, new_y);
	draw_new_player(game, hero);
}

// This function handles key press events.
// It takes the keycode and a pointer to the game state as parameters.
// If the escape key is pressed, it destroys the window, 
// frees the game map, and exits the program.
// If the 'w', 'a', 's', or 'd' key is pressed, 
// it updates the player's position and handles the movement.
int	key_press_handler(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x;
	new_y = game->player_y;
	if (keycode == 65307)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		free_map(game->map, game->map_height);
		exit(0);
	}
	else if (keycode == 119)
		new_y--;
	else if (keycode == 115)
		new_y++;
	else if (keycode == 97)
		new_x--;
	else if (keycode == 100)
		new_x++;
	handle_movement(game, new_x, new_y);
	return (0);
}
