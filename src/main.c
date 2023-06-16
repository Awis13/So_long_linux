/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awis <awis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:47:33 by awis              #+#    #+#             */
/*   Updated: 2023/06/13 17:59:25 by awis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// This function is a handler for the close event. 
// It takes no parameters and returns 0 after exiting the program.
int	close_handler(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

// This function reallocates memory.
// It takes a pointer to the memory and the new size as parameters.
// If the size is 0, it frees the memory and returns NULL. 
// If the pointer is NULL, it allocates new memory.
// If both are provided, it allocates new memory, 
// copies the old data to the new location, 
// frees the old memory, and returns a pointer to the new memory.

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(size));
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = (malloc(size));
	if (new_ptr)
	{
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}

// This is the main function of the program. 
// It takes the number of command line arguments and 
// an array of the arguments as parameters. 
// It opens the file provided as an argument, 
// checks for errors, and runs the program if everything is okay.

int	main(int argc, char **argv)
{
	int	fd;

	fd = open_file(argv[1]);
	if (argc != 2)
	{
		ft_printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	if (fd < 0)
		return (1);
	run_program(fd);
	return (0);
}

// This function frees the memory allocated for the sprites. 
// It takes a pointer to the sprites and a pointer to the MiniLibX 
// instance as parameters. It destroys the images associated with each sprite.

void	free_sprites(t_sprites *sprites, void *mlx_ptr)
{
	mlx_destroy_image(mlx_ptr, sprites->hero);
	mlx_destroy_image(mlx_ptr, sprites->floor);
	mlx_destroy_image(mlx_ptr, sprites->collectible);
	mlx_destroy_image(mlx_ptr, sprites->border);
	mlx_destroy_image(mlx_ptr, sprites->exit);
}
