/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:09:33 by cestevez          #+#    #+#             */
/*   Updated: 2023/10/16 17:12:04 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_map	*init_game(t_map *game)
{
	game = (t_map *)malloc(sizeof(t_map));
	if (!game)
		return (0);
	game->height = 0;
	game->width = 0;
	game->item = 0;
	game->exit = 0;
	game->start_y = 0;
	game->start_x = 0;
	game->moves = 0;
	game->matrix = NULL;
	game = init_game_2(game);
	return (game);
}

t_map	*init_game_2(t_map *game)
{
	game->mlx = NULL;
	game->txtr_ground = NULL;
	game->txtr_wall = NULL;
	game->txtr_exit = NULL;
	game->txtr_win = NULL;
	game->txtr_item = NULL;
	game->txtr_plyr = NULL;
	game->img_ground = NULL;
	game->img_wall = NULL;
	game->img_exit = NULL;
	game->img_win = NULL;
	game->img_item = NULL;
	game->img_plyr = NULL;
	game->score_collect = NULL;
	game->score_moves = NULL;
	return (game);
}

t_map	*init_map_copy(t_map *game, t_map *map_copy)
{
	map_copy = (t_map *)malloc(sizeof(t_map));
	if (!map_copy)
		return (0);
	map_copy->height = game->height;
	map_copy->width = game->width;
	map_copy->item = game->item;
	map_copy->exit = game->exit;
	map_copy->start_y = game->start_y;
	map_copy->start_x = game->start_x;
	map_copy->moves = game->moves;
	map_copy->matrix = game->matrix;
	init_map_copy_2(game, map_copy);
	return (map_copy);
}

t_map	*init_map_copy_2(t_map *game, t_map *map_copy)
{
	map_copy->mlx = game->mlx;
	map_copy->txtr_ground = game->txtr_ground;
	map_copy->txtr_wall = game->txtr_wall;
	map_copy->txtr_exit = game->txtr_exit;
	map_copy->txtr_win = game->txtr_win;
	map_copy->txtr_item = game->txtr_item;
	map_copy->txtr_plyr = game->txtr_plyr;
	map_copy->img_ground = game->img_ground;
	map_copy->img_wall = game->img_wall;
	map_copy->img_exit = game->img_exit;
	map_copy->img_win = game->img_win;
	map_copy->img_item = game->img_item;
	map_copy->img_plyr = game->img_plyr;
	map_copy->score_collect = game->score_collect;
	map_copy->score_moves = game->score_moves;
	return (map_copy);
}

int	copy_map(t_map *game, t_map *map_copy)
{
	size_t	y;
	size_t	x;

	y = 0;
	map_copy->matrix = (char **)malloc(sizeof(char *) * (map_copy->height));
	if (!map_copy->matrix)
		return (0);
	while (y < map_copy->height)
	{
		x = 0;
		map_copy->matrix[y] = malloc((map_copy->width + 1) * sizeof(char));
		if (!map_copy->matrix[y])
			return (free_inside_copy(map_copy));
		while (x < map_copy->width)
		{
			map_copy->matrix[y][x] = game->matrix[y][x];
			x++;
		}
		map_copy->matrix[y][x] = '\0';
		y++;
	}
	return (1);
}
