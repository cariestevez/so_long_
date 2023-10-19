/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:06:59 by cestevez          #+#    #+#             */
/*   Updated: 2023/10/17 16:55:04 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_and_terminate(t_map	*game)
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
	mlx_terminate(game->mlx);
	game->mlx = NULL;
	free(game);
	game = NULL;
}

void	free_textures(t_map	*game)
{
	if (game->txtr_ground)
		mlx_delete_texture(game->txtr_ground);
	if (game->txtr_wall)
		mlx_delete_texture(game->txtr_wall);
	if (game->txtr_exit)
		mlx_delete_texture(game->txtr_exit);
	if (game->txtr_win)
		mlx_delete_texture(game->txtr_win);
	if (game->txtr_item)
		mlx_delete_texture(game->txtr_item);
	if (game->txtr_plyr)
		mlx_delete_texture(game->txtr_plyr);
}

void	free_failure_exit(t_map *game)
{
	free_textures(game);
	free_and_terminate(game);
	exit(EXIT_FAILURE);
}

int	free_success_exit(t_map *game)
{
	free_textures(game);
	free_and_terminate(game);
	return (EXIT_SUCCESS);
}
