/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awis <awis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:57:01 by awis              #+#    #+#             */
/*   Updated: 2023/06/13 19:57:25 by awis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// This function loads the floor and hero sprites.
// It takes a pointer to the game state and pointers 
// to the floor and hero sprites as parameters.
// It loads the sprites from the corresponding texture files.
void	load_sprites(t_game *game, void **floor, void **hero)
{
	*floor = load_sprite(game->mlx_ptr, "textures/floor.xpm");
	*hero = load_sprite(game->mlx_ptr, "textures/hero.xpm");
}

// This function checks if a new position is 
// within the boundaries of the game map.
// It takes a pointer to the game state and the 
// new x and y coordinates as parameters.
// It returns 1 if the new position is within the 
// boundaries and 0 otherwise.
int	check_boundaries(t_game *game, int new_x, int new_y)
{
	return (!(new_x < 0 || new_x >= game->map_width
			|| new_y < 0 || new_y >= game->map_height));
}

// This function checks if a new position is a wall.
// It takes a pointer to the game state and the 
// new x and y coordinates as parameters.
// It returns 1 if the new position is not a wall and 0 otherwise.
int	check_wall(t_game *game, int new_x, int new_y)
{
	return (!(game->map[new_y][new_x] == '1'));
}
// This function handles the player reaching the exit.
// It takes a pointer to the game state and 
// the new x and y coordinates as parameters.
// If the new position is the exit and there are no collectibles left, 
// it prints a congratulations message, destroys the window, 
// frees the game map, and exits the program.

void	handle_exit(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'E' && game->collectibles == 0)
	{
		printf("Congratulations!\n");
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		free_map(game->map, game->map_height);
		exit(EXIT_SUCCESS);
	}
}

// This function handles the player collecting a collectible.
// It takes a pointer to the game state and 
// the new x and y coordinates as parameters.
// If the new position is a collectible, it changes 
// the position to a floor, decreases the number 
// of collectibles, and prints a message.
void	handle_collectible(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'C')
	{
		game->map[new_y][new_x] = '0';
		if (game->collectibles > 0)
		{
			game->collectibles--;
		}
		ft_printf("Collectible collected! %d remaining.\n", game->collectibles);
	}
}
