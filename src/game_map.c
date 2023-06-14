/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awis <awis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:05:37 by awis              #+#    #+#             */
/*   Updated: 2023/06/13 20:11:58 by awis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'C'
		|| c == 'P' || c == 'E' || c == '\n');
}

char	**copy_map(char **map, int map_width, int map_height)
{
	int		y;
	char	**copy;

	y = 0;
	copy = malloc(map_height * sizeof(char *));
	if (copy == NULL)
	{
		ft_printf("Error: Memory allocation failed\n");
		return (NULL);
	}
	while (y < map_height)
	{
		copy[y] = copy_row(map[y], map_width);
		if (copy[y] == NULL)
		{
			ft_printf("Error: Memory allocation failed\n");
			free_map(copy, y);
			return (NULL);
		}
		y++;
	}
	return (copy);
}

int	check_map_closed(char **map, int map_width, int map_height)
{
	int	x;
	int	y;

	y = 0;
	while (y < map_height)
	{
		x = 0;
		while (x < map_width)
		{
			if ((x == 0 || x == map_width - 1 || y == 0
					|| y == map_height - 1) && map[y][x] != '1')
			{
				ft_printf("Error: Map is not surrounded by walls\n");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

void	flood_fill(t_mapdata data, int x, int y)
{
	if (x < 0 || x >= data.map_width || y < 0 || y >= data.map_height
		|| data.map[y][x] == '1' || data.map[y][x] == 'F')
	{
		return ;
	}
	data.map[y][x] = 'F';
	flood_fill(data, x + 1, y);
	flood_fill(data, x - 1, y);
	flood_fill(data, x, y + 1);
	flood_fill(data, x, y - 1);
}
