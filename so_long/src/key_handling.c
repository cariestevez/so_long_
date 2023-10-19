/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:12:14 by cestevez          #+#    #+#             */
/*   Updated: 2023/10/17 16:44:18 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	becauseofnormi(t_map *game)
{
	int	x;
	int	y;

	x = game->img_exit->instances[0].x;
	y = game->img_exit->instances[0].y;
	mlx_image_to_window(game->mlx, game->img_win, x, y);
}

void	check_surroundings(t_map *game, size_t y, size_t x, char c)
{
	size_t	i;

	i = -1;
	if (game->matrix[y][x] == EXIT && game->item == 0)
	{
		move_player(game, c);
		ft_printf("YOU WON! :D\n");
		return (mlx_close_window(game->mlx));
	}
	else if (game->matrix[y][x] == COLLECT)
	{
		while (++i < game->img_item->count)
		{
			if ((game->img_item->instances[i].x / 32 == (int)x)
				&& (game->img_item->instances[i].y / 32 == (int)y))
				game->img_item->instances[i].enabled = false;
		}
		game->matrix[y][x] = GROUND;
		game->item--;
		ft_printf("%d rollerskates to go...\n", game->item);
		if (game->item == 0)
			becauseofnormi(game);
	}
	move_player(game, c);
}

void	move_player(t_map *game, char c)
{
	if (c == 'l')
		game->img_plyr->instances[0].x -= 32;
	else if (c == 'r')
		game->img_plyr->instances[0].x += 32;
	else if (c == 'u')
		game->img_plyr->instances[0].y -= 32;
	else if (c == 'd')
		game->img_plyr->instances[0].y += 32;
	game->moves++;
	ft_printf("moves: %d\n", game->moves);
}

void	my_keyhook(mlx_key_data_t keydata, void	*param)
{
	size_t	y;
	size_t	x;
	t_map	*game;

	game = (void *)param;
	y = game->img_plyr->instances[0].y / 32;
	x = game->img_plyr->instances[0].x / 32;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	else if ((keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		&& (game->matrix[y][x - 1] != WALL))
		check_surroundings(game, y, x - 1, 'l');
	else if ((keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		&& (game->matrix[y + 1][x] != WALL))
		check_surroundings(game, y + 1, x, 'd');
	else if ((keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		&& (game->matrix[y][x + 1] != WALL))
		check_surroundings(game, y, x + 1, 'r');
	else if ((keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		&& (game->matrix[y - 1][x] != WALL))
		check_surroundings(game, y - 1, x, 'u');
}
