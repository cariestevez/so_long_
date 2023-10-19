/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:58:59 by cestevez          #+#    #+#             */
/*   Updated: 2023/10/17 16:45:37 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	create_images(t_map *game)
{
	game->txtr_ground = mlx_load_png("textures/tile.png");
	game->txtr_wall = mlx_load_png("textures/wall_cactus.png");
	game->txtr_exit = mlx_load_png("textures/exit_world.png");
	game->txtr_win = mlx_load_png("textures/win.png");
	game->txtr_item = mlx_load_png("textures/collect_roller.png");
	game->txtr_plyr = mlx_load_png("textures/player_cat.png");
	if (!game->txtr_plyr || !game->txtr_item || !game->txtr_exit
		|| !game->txtr_wall || !game->txtr_ground)
		free_failure_exit(game);
	game->img_ground = mlx_texture_to_image(game->mlx, game->txtr_ground);
	game->img_wall = mlx_texture_to_image(game->mlx, game->txtr_wall);
	game->img_exit = mlx_texture_to_image(game->mlx, game->txtr_exit);
	game->img_win = mlx_texture_to_image(game->mlx, game->txtr_win);
	game->img_item = mlx_texture_to_image(game->mlx, game->txtr_item);
	game->img_plyr = mlx_texture_to_image(game->mlx, game->txtr_plyr);
	if (!game->img_plyr || !game->img_item || !game->img_exit
		|| !game->img_wall || !game->img_ground)
		free_failure_exit(game);
}

void	display_images(t_map *game)
{
	size_t	y;
	size_t	x;

	x = 0;
	y = 0;
	while (y < game->height)
	{
		x = -1;
		while (++x < game->width)
		{
			mlx_image_to_window(game->mlx, game->img_ground, x * 32, y * 32);
			if (game->matrix[y][x] == WALL)
				mlx_image_to_window(game->mlx, game->img_wall, x * 32, y * 32);
			if (game->matrix[y][x] == EXIT)
				mlx_image_to_window(game->mlx, game->img_exit, x * 32, y * 32);
			if (game->matrix[y][x] == COLLECT)
				mlx_image_to_window(game->mlx, game->img_item, x * 32, y * 32);
			if (game->matrix[y][x] == PLAYER)
				mlx_image_to_window(game->mlx, game->img_plyr, x * 32, y * 32);
		}
		y++;
	}
	layering(game);
}

void	layering(t_map *game)
{
	size_t	i;

	i = -1;
	while (++i < game->img_ground->count)
		mlx_set_instance_depth(&game->img_ground->instances[i], 0);
	i = -1;
	while (++i < game->img_wall->count)
		mlx_set_instance_depth(&game->img_wall->instances[i], 1);
	i = -1;
	while (++i < game->img_exit->count)
		mlx_set_instance_depth(&game->img_exit->instances[i], 1);
	i = -1;
	while (++i < game->img_item->count)
		mlx_set_instance_depth(&game->img_item->instances[i], 1);
	mlx_set_instance_depth(&game->img_plyr->instances[0], 3);
}
