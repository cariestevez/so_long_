/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cestevez <cestevez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:26:01 by cestevez          #+#    #+#             */
/*   Updated: 2023/10/19 15:44:20 by cestevez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	free_gnl_buff(int fd, char *line)
{
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	pre_parsing_check(t_map *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
	{
		ft_printf("Error\nMap is empty!\n");
		return (0);
	}
	game->width = ft_strlen(line) - 1;
	while (line != 0)
	{
		if (check_shape(game, line) == 0 || invalid_char(line) == 1)
			return (free_gnl_buff(fd, line));
		game->height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (1);
}

int	check_shape(t_map *game, char *line)
{
	size_t	temp_width;

	temp_width = 0;
	if (line != NULL)
	{
		temp_width = ft_strlen(line) - 1;
		if (line[temp_width] != '\n')
			temp_width++;
		if (temp_width != game->width && line[0] != '\0' && line[0] != ' ')
		{
			ft_printf("Error\nShape not regular. Map not valid.\n");
			free(line);
			return (0);
		}
	}
	return (1);
}

int	invalid_char(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (1);
	while (line != NULL)
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == 'P'
			|| line[i] == 'E' || line[i] == 'C')
			i++;
		else if (line[i] == '\0' || line[i] == '\n')
			return (0);
		else
		{
			ft_printf("Error\nInvalid character(s). Map not valid.\n");
			free(line);
			return (1);
		}
	}
	return (0);
}
