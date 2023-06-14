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

void	load_sprites(t_game *game, void **floor, void **hero)
{
	*floor = load_sprite(game->mlx_ptr, "textures/floor.xpm");
	*hero = load_sprite(game->mlx_ptr, "textures/hero.xpm");
}

int	check_boundaries(t_game *game, int new_x, int new_y)
{
	return (!(new_x < 0 || new_x >= game->map_width
			|| new_y < 0 || new_y >= game->map_height));
}

int	check_wall(t_game *game, int new_x, int new_y)
{
	return (!(game->map[new_y][new_x] == '1'));
}

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
