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

int	close_handler(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

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
