/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awis <awis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 00:04:02 by nipostni          #+#    #+#             */
/*   Updated: 2023/06/13 20:32:07 by awis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "include/libft.h"

static void	free_and_assign(char **ptr, char *new_val)
{
	free(*ptr);
	*ptr = new_val;
}

static char	*read_and_append(int fd, char *buf, char *stash)
{
	int		bytes_read;
	char	*tmp_stash;

	while (42)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buf);
			if (stash)
				free(stash);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		if (!stash)
			stash = ft_strdup(buf);
		else
		{
			tmp_stash = ft_strjoin(stash, buf);
			free_and_assign(&stash, tmp_stash);
		}
		if (ft_strchr(stash, '\n') || bytes_read == 0)
			break ;
	}
	return (stash);
}

static char	*get_one_line(int fd, char *stash)
{
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	stash = read_and_append(fd, buf, stash);
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			len;
	char		*tmp_stash;

	stash = get_one_line(fd, stash);
	if (!stash)
		return (NULL);
	len = ft_strchr(stash, '\n') - stash;
	line = ft_substr(stash, 0, len + 1);
	tmp_stash = ft_substr(stash, len + 1, (ft_strlen(stash) - len));
	free_and_assign(&stash, tmp_stash);
	if (stash && stash[0] == '\0')
		free_and_assign(&stash, NULL);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
