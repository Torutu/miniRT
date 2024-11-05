/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:42:29 by sataskin          #+#    #+#             */
/*   Updated: 2024/11/05 14:27:13 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int get_values(char *line, t_minirt *rt)
{
    char	**values;

	values = ft_split(line, '\n');
    if (!values)
    {
        write(2, "Error\nFT_SPLIT FAILED", 22);
        return (1);  // Return error to handle failed malloc.
    }
    if (ft_strcmp(values[0], "A") == 0)
        add_ambient(values, rt);
    else if (ft_strcmp(values[0], "C") == 0)
        add_camera(values, rt);
    else if (ft_strcmp(values[0], "L") == 0)
        add_light(values, rt);
    else if (ft_strcmp(values[0], "sp") == 0)
        add_sphere(values, rt);
    else if (ft_strcmp(values[0], "pl") == 0)
        add_plane(values, rt);
    else if (ft_strcmp(values[0], "cy") == 0)
        add_cylinder(values, rt);
    else
    {
        write(2, "Error\nInvalid input in file", 28);
        return (1);
    }
    return (0);
}


void check_content(char *file, t_minirt *rt)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	(void)rt;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (get_values(line, rt) == 1)
		{
			close (fd); // add freeing of linked list
			exit (1);
		}
		free(line);
	}
	close(fd);
}

/*char	*get_line(int fd)
{
	char	*line;
	char	*str;
	char	*temp;

	line = ft_strdup("");
	if (!line)
		exit_none("Malloc fail");
	while (1)
	{
		str = get_next_line(fd);
		temp = line;
		if (str == NULL)
			break ;
		if (ft_strcmp(str, "\n") == 0)
			exit_dstr(line, str, "Extra new line");
		line = ft_strjoin(temp, str);
		if (!temp)
			exit_str(str, "Malloc fail");
		free(temp);
		free(str);
	}
	if (str)
		free(str);
	check_char(line);
	return (line);
}*/
