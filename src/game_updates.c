/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_updates.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awis <awis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:43:42 by awis              #+#    #+#             */
/*   Updated: 2023/06/13 19:55:24 by awis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// This function removes the old player sprite from the game map.
// It takes a pointer to the game state and a pointer 
// to the floor sprite as parameters.
// It draws a floor block at the current player position.
void	remove_old_player(t_game *game, void *floor)
{
	draw_block(game, floor, game->player_x, game->player_y);
}

// This function updates the player's position in the game state.
// It takes a pointer to the game state 
// and the new x and y coordinates as parameters.
// It changes the old player position to a floor, the new position to a player, 
// and updates the player coordinates and step count in the game state.
void	update_position(t_game *game, int new_x, int new_y)
{
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	game->steps++;
	ft_printf("Turn number %d\n", game->steps);
}

// This function draws the new player sprite on the game map.
// It takes a pointer to the game state and 
// a pointer to the hero sprite as parameters.
// It draws a hero block at the current player position.
void	draw_new_player(t_game *game, void *hero)
{
	draw_block(game, hero, game->player_x, game->player_y);
}
