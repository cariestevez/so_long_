/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:27:12 by cestevez          #+#    #+#             */
/*   Updated: 2023/10/19 16:04:35 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	validate_map(t_map *game)
{
	if (check_walls(game) == 0 || count_exit(game) == 0
		|| count_plyr(game) != 1 || count_item(game) == 0)
	{
		if (count_plyr(game) != 1)
			ft_printf("Error\nToo many or no player(s). ");
		ft_printf("Map not valid.\n");
		return (0);
	}
	if (find_path(game) == 0)
		return (0);
	return (1);
}

int	find_path(t_map *game)
{
	int		failure;
	t_map	*map_copy;

	failure = 0;
	map_copy = NULL;
	map_copy = init_map_copy(game, map_copy);
	if (map_copy == NULL)
		return (0);
	if (copy_map(game, map_copy) == 0)
	{
		free(map_copy);
		return (0);
	}
	flood_fill(map_copy, map_copy->start_y, map_copy->start_x);
	if (map_copy->exit != 1 || map_copy->item != 0)
		failure = 1;
	free_inside_copy(map_copy);
	free(map_copy);
	map_copy = NULL;
	if (failure == 1)
		return (non_reachable());
	return (1);
}

int	non_reachable(void)
{
	ft_printf("Error\nExit/collectible(s) not reachable. Map not valid.\n");
	return (0);
}

void	flood_fill(t_map *map_copy, size_t y, size_t x)
{
	if (y < 0 || y >= map_copy->height || x < 0 || x >= map_copy->width)
		return ;
	if (map_copy->matrix[y][x] == 'x' || map_copy->matrix[y][x] == WALL)
		return ;
	if (map_copy->matrix[y][x] == EXIT)
	{
		map_copy->matrix[y][x] = 'x';
		map_copy->exit++;
	}
	else if (map_copy->matrix[y][x] == COLLECT)
	{
		map_copy->matrix[y][x] = 'x';
		map_copy->item--;
	}
	else if (map_copy->matrix[y][x] == GROUND)
		map_copy->matrix[y][x] = 'x';
	if (map_copy->exit == 1 && map_copy->item == 0)
		return ;
	flood_fill(map_copy, y, x + 1);
	flood_fill(map_copy, y, x - 1);
	flood_fill(map_copy, y - 1, x);
	flood_fill(map_copy, y + 1, x);
}
