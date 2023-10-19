/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_checks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:55:40 by cestevez          #+#    #+#             */
/*   Updated: 2023/10/19 16:04:46 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_walls(t_map *game)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (((y == 0 || y == game->height - 1)
					&& game->matrix[y][x] != WALL)
					|| ((y != 0 && y != game->height - 1)
					&& (game->matrix[y][0] != WALL
					|| game->matrix[y][game->width - 1] != WALL)))
			{
				ft_printf("Error\nWalls missing. ");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	count_exit(t_map *game)
{
	int		exit;
	size_t	y;
	size_t	x;

	exit = 0;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->matrix[y][x] == EXIT)
				exit++;
			x++;
		}
		y++;
	}
	if (exit != 1)
	{
		ft_printf("Error\nToo many or no exit(s). ");
		return (0);
	}
	return (1);
}

int	count_plyr(t_map *game)
{
	int		player;
	size_t	y;
	size_t	x;

	player = 0;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width - 1)
		{
			if (game->matrix[y][x] == PLAYER)
			{
				game->start_y = y;
				game->start_x = x;
				player++;
			}
			x++;
		}
		y++;
	}
	return (player);
}

int	count_item(t_map *game)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width - 1)
		{
			if (game->matrix[y][x] == COLLECT)
				game->item++;
			x++;
		}
		y++;
	}
	if (game->item < 1)
	{
		ft_printf("Error\nCollectible(s) missing. ");
		return (0);
	}
	return (1);
}
