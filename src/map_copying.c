/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_copying.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awis <awis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:38:56 by awis              #+#    #+#             */
/*   Updated: 2023/06/13 19:39:11 by awis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// This function copies a row from the game map.
// It takes the row and its width as parameters.
// It allocates memory for the copy and copies each 
// character from the original row.
// It returns the copied row.
char	*copy_row(char *row, int row_width)
{
	char	*copy;
	int		x;

	x = 0;
	copy = malloc((row_width + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	while (x < row_width)
	{
		copy[x] = row[x];
		x++;
	}
	copy[row_width] = '\0';
	return (copy);
}
