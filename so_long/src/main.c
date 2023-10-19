/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:20:07 by cestevez          #+#    #+#             */
/*   Updated: 2023/10/18 16:18:33 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_mlxerror(t_map *game)
{
	ft_printf("%s\n", mlx_strerror(mlx_errno));
	free_matrix_exit(game);
}

int	ft_errors(int fd, t_map *game)
{
	if (fd < 0)
	{
		ft_printf("Unable to open the file\n");
		return (free_and_exit(game));
	}
	else
	{
		close(fd);
		return (free_and_exit(game));
	}
}

int	check_file_extension(int argc, char **argv)
{
	size_t	len;

	len = 0;
	if (argc != 2)
	{
		ft_printf("Invalid arguments! Usage: %s <map_file.ber>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	len = strlen(argv[1]);
	if (len < 4 || strcmp(argv[1] + len - 4, ".ber") != 0)
	{
		ft_printf("Invalid file extension! File must have .ber extension.\n");
		return (EXIT_FAILURE);
	}
	return (0);
}

int	parse_and_validate(t_map *game, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_errors(fd, game));
	if (pre_parsing_check(game, fd) == 0)
		return (ft_errors(fd, game));
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_errors(fd, game));
	if (parse_map(fd, game) == 0)
		return (ft_errors(fd, game));
	close(fd);
	if (validate_map(game) == 0)
		return (free_matrix_exit(game));
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	*game;

	game = NULL;
	if (check_file_extension(argc, argv) == 1)
		return (EXIT_FAILURE);
	game = init_game(game);
	if (!game)
		return (EXIT_FAILURE);
	if (parse_and_validate(game, argv) == 1)
		return (EXIT_FAILURE);
	game->mlx = mlx_init(32 * game->width, 32 * game->height, "so_long", true);
	if (!game->mlx)
		ft_mlxerror(game);
	create_images(game);
	display_images(game);
	mlx_key_hook(game->mlx, &my_keyhook, game);
	mlx_loop(game->mlx);
	return (free_success_exit(game));
}
