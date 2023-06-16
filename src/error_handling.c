/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awis <awis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:23:00 by awis              #+#    #+#             */
/*   Updated: 2023/06/13 19:55:46 by awis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// This function prints an error message to the console.
// It takes a string as a parameter and returns 0 after printing the message.
int	print_error(char *msg)
{
	ft_printf("%s\n", msg);
	return (0);
}

// This function updates the coordinates of the game elements.
// It takes the game map and the coordinates array as parameters, 
// along with the x and y positions.
// Depending on the character at the given position, 
// it increments the corresponding element in the coordinates array.
void	update_coords(char **map, int *coords, int x, int y)
{
	if (map[y][x] == 'E')
		coords[0]++;
	else if (map[y][x] == 'C')
		coords[1]++;
	else if (map[y][x] == 'P')
		coords[2]++;
}

// This function validates the conditions of the game map.
// It takes the coordinates array as a parameter.
// It checks if there is exactly one exit, at least one 
// collectible, and exactly one starting position.
// If any of these conditions are not met, 
// it prints an error message and returns 0.
// If all conditions are met, it returns 1.
int	validate_conditions(int *coords)
{
	if (coords[0] != 1)
	{
		ft_printf("Error: Map should have exactly 1 exit. ");
		ft_printf("Found %d exit(s).\n", coords[0]);
		return (0);
	}
	if (coords[1] < 1)
	{
		ft_printf("Error: Map should have at least 1 collectible. ");
		ft_printf("Found %d collectible(s).\n", coords[1]);
		return (0);
	}
	if (coords[2] != 1)
	{
		ft_printf("Error: Map should have exactly 1 starting position. ");
		ft_printf("Found %d starting position(s).\n", coords[2]);
		return (0);
	}
	return (1);
}

// This function checks for unreachable areas in the game map.
// It takes the game map and its width and height as parameters.
// It iterates over the map and if it finds a '0', 'C', or 'E' 
// character, it calls the print_error function and returns 0.
// If no unreachable areas are found, it returns 1.
int	check_unreachable_areas(char **map, int map_width, int map_height)
{
	int	y;
	int	x;

	y = 0;
	while (y < map_height)
	{
		x = 0;
		while (x < map_width)
		{
			if (map[y][x] == '0' || map[y][x] == 'C' || map[y][x] == 'E')
				return (print_error("Error: Map has unreachable areas"));
			x++;
		}
		y++;
	}
	return (1);
}
