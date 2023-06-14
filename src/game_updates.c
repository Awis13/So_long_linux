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

void	remove_old_player(t_game *game, void *floor)
{
	draw_block(game, floor, game->player_x, game->player_y);
}

void	update_position(t_game *game, int new_x, int new_y)
{
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	game->steps++;
	ft_printf("Turn number %d\n", game->steps);
}

void	draw_new_player(t_game *game, void *hero)
{
	draw_block(game, hero, game->player_x, game->player_y);
}
