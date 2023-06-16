/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awis <awis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:10:46 by awis              #+#    #+#             */
/*   Updated: 2023/06/13 19:56:47 by awis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// This function validates the game map.
// It takes the file descriptor and a pointer to the game state as parameters.
// It reads the map from the file, checks if it is valid, 
// and updates the game state.
// It returns 1 if the map is valid and 0 otherwise.
int	map_validate(int fd, t_game *game)
{
	char	*line;
	char	**map_copy;

	line = get_next_line(fd);
	if (line == NULL)
		return (print_error("Error: Empty map"));
	game->map_width = get_line_width(line);
	game->map_height = 1;
	game->map = malloc(sizeof(char *));
	if (game->map == NULL)
		return (print_error("Error: Memory allocation failed"));
	game->map[0] = line;
	ft_printf("%s", line);
	if (!validate_map(fd, game, line))
		return (0);
	map_copy = copy_map(game->map, game->map_width, game->map_height);
	if (map_copy == NULL)
		return (0);
	if (!check_map_path(map_copy, game->map_width, game->map_height))
	{
		free_map(map_copy, game->map_height);
		return (0);
	}
	free_map(map_copy, game->map_height);
	return (1);
}

// This function loads a sprite from a file.
// It takes a pointer to the MiniLibX instance and the file path as parameters.
// It returns the loaded sprite or NULL if the sprite could not be loaded.
void	*load_sprite(void *mlx_ptr, char *filepath)
{
	int		width;
	int		height;
	void	*sprite;

	sprite = mlx_xpm_file_to_image(mlx_ptr, filepath, &width, &height);
	if (sprite == NULL)
	{
		ft_printf("Error: could not load sprite %s\n", filepath);
		return (NULL);
	}
	return (sprite);
	mlx_destroy_image(mlx_ptr, sprite);
}

// This function draws a block at a given position in the game.
// It takes a pointer to the game state, the sprite to draw, 
// and the x and y coordinates as parameters.
// It draws the sprite at the given position.
void	draw_block(t_game *game, void *sprite, int x, int y)
{
	int	offset_x;
	int	offset_y;

	offset_x = 0;
	offset_y = 0;
	while (offset_x <= 1)
	{
		offset_y = 0;
		while (offset_y <= 1)
		{
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, sprite,
				x * BLOCK_SIZE + offset_x, y * BLOCK_SIZE + offset_y);
			offset_y++;
		}
		offset_x++;
	}
}

// This function draws the game map.
// It takes a pointer to the game state as parameters.
// It loads the sprites for the different types of blocks 
// and draws them at their respective positions.
void	draw_map(t_game *game)
{
	t_sprites	sprites;

	sprites.hero = load_sprite(game->mlx_ptr, "textures/hero.xpm");
	sprites.floor = load_sprite(game->mlx_ptr, "textures/floor.xpm");
	sprites.collectible = load_sprite(game->mlx_ptr,
			"textures/collectible.xpm");
	sprites.border = load_sprite(game->mlx_ptr, "textures/border.xpm");
	sprites.exit = load_sprite(game->mlx_ptr, "textures/exit.xpm");
	if (sprites.hero == NULL || sprites.floor == NULL || sprites.collectible
		== NULL || sprites.border == NULL || sprites.exit == NULL)
	{
		mlx_destroy_image(game->mlx_ptr, sprites.hero);
		mlx_destroy_image(game->mlx_ptr, sprites.floor);
		mlx_destroy_image(game->mlx_ptr, sprites.collectible);
		mlx_destroy_image(game->mlx_ptr, sprites.border);
		mlx_destroy_image(game->mlx_ptr, sprites.exit);
		return ;
	}
	draw_blocks(game, &sprites);
	mlx_destroy_image(game->mlx_ptr, sprites.hero);
	mlx_destroy_image(game->mlx_ptr, sprites.floor);
	mlx_destroy_image(game->mlx_ptr, sprites.collectible);
	mlx_destroy_image(game->mlx_ptr, sprites.border);
	mlx_destroy_image(game->mlx_ptr, sprites.exit);
}
