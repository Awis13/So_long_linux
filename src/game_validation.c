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

// This function frees the memory allocated for the game map.
// It takes the game map and its height as parameters.
// It frees each row of the map and then the map itself.
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

// This function checks if there are any unreachable areas in the game map.
// It takes the game map and its width and height as parameters.
// It performs a flood fill operation starting from the player's 
// position and then checks for unreachable areas.
// It returns 1 if there are no unreachable areas and 0 otherwise.
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

// This function checks if the game map meets certain conditions.
// It takes the game map and its width and height, 
// and a pointer to the game state as parameters.
// It counts the number of exits, collectibles, 
// and starting positions in the map and validates these counts.
// It also updates the number of collectibles in the game state.
// It returns 1 if the conditions are met and 0 otherwise.
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

// This function gets the width of a line in the game map.
// It takes a line as a parameter and returns the number 
// of characters before the newline or null character.
int	get_line_width(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	return (i);
}
