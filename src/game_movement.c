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
