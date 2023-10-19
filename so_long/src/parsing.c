/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:25:04 by cestevez          #+#    #+#             */
/*   Updated: 2023/10/18 16:26:20 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	parse_map(int fd, t_map *game)
{
	size_t	y;

	y = 0;
	game->matrix = (char **)malloc(sizeof(char *) * (game->height));
	if (!game->matrix)
		return (0);
	while (y < game->height)
	{
		game->matrix[y] = (char *)malloc((game->width + 1) * sizeof(char));
		if (!game->matrix[y])
			return (free_matrix_exit(game));
		save_line(game, y, fd);
		ft_printf("\t%s\n", game->matrix[y]);
		y++;
	}
	return (1);
}

void	save_line(t_map *game, size_t y, int fd)
{
	size_t	x;
	char	*line;

	x = 0;
	line = get_next_line(fd);
	while (x < game->width)
	{
		game->matrix[y][x] = line[x];
		x++;
	}
	game->matrix[y][x] = '\0';
	free(line);
}
