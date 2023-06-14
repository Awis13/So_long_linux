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
}

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

void	draw_map(t_game *game)
{
	t_sprites	sprites;

	sprites.hero = load_sprite(game->mlx_ptr, "textures/hero.xpm");
	sprites.floor = load_sprite(game->mlx_ptr, "textures/floor.xpm");
	sprites.collectible = load_sprite(game->mlx_ptr,
			"textures/collectible.xpm");
	sprites.border = load_sprite(game->mlx_ptr, "textures/border.xpm");
	sprites.exit = load_sprite(game->mlx_ptr, "textures/exit.xpm");
	if (sprites.hero == NULL || sprites.floor == NULL
		|| sprites.collectible == NULL || sprites.border == NULL
		|| sprites.exit == NULL)
		return ;
	draw_blocks(game, &sprites);
}
