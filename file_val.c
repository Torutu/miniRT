/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:39:46 by sataskin          #+#    #+#             */
/*   Updated: 2025/01/09 14:08:24 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	check_dir(char *file)
{
	int	fd;

	fd = open(file, O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		write(2, "Error\nThis is a directory!\n", 28);
		exit(1);
	}
}

static void	check_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		write(2, "Error\nCould not open file\n", 27);
		exit(1);
	}
	close(fd);
}

static void	check_file_format(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i < 3)
	{
		write(2, "Error\nInvalid file name\n", 25);
		exit(1);
	}
	if ((ft_strcmp(&str[i - 3], ".rt")) != 0)
	{
		write(2, "Error\nInvalid file name\n", 25);
		exit(1);
	}
}

void	check_valid(char *file)
{
	check_file_format(file);
	check_dir(file);
	check_file(file);
}
