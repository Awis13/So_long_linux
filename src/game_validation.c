/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awis <awis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:06:04 by awis              #+#    #+#             */
/*   Updated: 2023/06/13 21:01:20 by awis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	free_map(char **map, int map_height)
{
	int	y;

	y = 0;
	while (y < map_height)
	{
		free(map[y]);
		y++;
	}
	free(map);
}

int	check_map_path(char **map, int map_width, int map_height)
{
	int			y;
	int			x;
	t_mapdata	data;

	data.map = map;
	data.map_width = map_width;
	data.map_height = map_height;
	y = 0;
	while (y < map_height)
	{
		x = 0;
		while (x < map_width)
		{
			if (map[y][x] == 'P')
				flood_fill(data, x, y);
			x++;
		}
		y++;
	}
	return (check_unreachable_areas(map, map_width, map_height));
}

int	check_map_conditions(char **map, int map_width,
	int map_height, t_game *game)
{
	int	coords[3];
	int	x;
	int	y;

	coords[0] = 0;
	coords[1] = 0;
	coords[2] = 0;
	y = 0;
	while (y < map_height)
	{
		x = 0;
		while (x < map_width)
		{
			update_coords(map, coords, x, y);
			x++;
		}
		y++;
	}
	if (!validate_conditions(coords))
		return (0);
	game->collectibles = coords[1];
	return (1);
}

int	get_line_width(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	return (i);
}
