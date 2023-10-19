/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:05:50 by cestevez          #+#    #+#             */
/*   Updated: 2023/10/16 17:06:40 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	free_inside_copy(t_map *map_copy)
{
	size_t	y;

	y = 0;
	while (y <= map_copy->height - 1)
	{
		free(map_copy->matrix[y]);
		y++;
	}
	free(map_copy->matrix);
	map_copy->matrix = NULL;
	return (0);
}

int	free_matrix_exit(t_map *game)
{
	size_t	y;

	y = 0;
	while (y < game->height)
	{
		free(game->matrix[y]);
		y++;
	}
	free(game->matrix);
	game->matrix = NULL;
	return (free_and_exit(game));
}

int	free_and_exit(t_map *game)
{
	free(game);
	game = NULL;
	exit(EXIT_FAILURE);
}
