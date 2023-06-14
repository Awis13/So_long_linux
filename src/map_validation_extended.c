/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_extended.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awis <awis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:56:11 by awis              #+#    #+#             */
/*   Updated: 2023/06/13 19:56:17 by awis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	validate_map(int fd, t_game *game, char *line)
{
	line = get_next_line(fd);
	while (line && (get_line_width(line) == game->map_width))
	{
		game->map_height++;
		game->map = realloc(game->map, game->map_height * sizeof(char *));
		if (game->map == NULL)
		{
			ft_printf("Error: Memory allocation failed\n");
			return (0);
		}
		game->map[game->map_height - 1] = line;
		ft_printf("%s", line);
		line = get_next_line(fd);
	}
	if (!line)
	{
		if (validate_map_size(game) || validate_map_conditions(game)
			|| validate_map_closed(game))
			return (0);
		return (1);
	}
	ft_printf("Error: Inconsistent map width\n");
	free(line);
	return (0);
}

int	validate_map_size(t_game *game)
{
	ft_printf("\nMap validation successful\n");
	ft_printf("\nmap_height = %d\n", game->map_height);
	ft_printf("map_width = %d\n", game->map_width);
	if (!check_map_conditions(game->map, game->map_width,
			game->map_height, game))
		return (1);
	return (0);
}

int	validate_map_closed(t_game *game)
{
	if (!check_map_closed(game->map, game->map_width, game->map_height))
		return (1);
	return (0);
}
