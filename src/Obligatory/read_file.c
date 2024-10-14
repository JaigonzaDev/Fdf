/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:23:41 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/14 17:22:16 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 *	Count how many char keys are in the give line
 */
int	ft_wdcounter(char *line, char key)
{
	int	width;
	int	in_word;

	width = 0;
	in_word = 0;
	while (*line)
	{
		if (*line != key && in_word == 0)
		{
			in_word = 1;
			width++;
		}
		else if (*line == key)
			in_word = 0;
		line++;
	}
	return (width);
}

/*
 *	Get the height counting the lines returned by get_next_line
 */
int	get_height(char *file_name)
{
	char	*line;
	int		fd;
	int		height;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (-1);
	height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

/*
 * Get the width counting the ' ' of the first line
 */
int	get_width(char *file_name)
{
	int		width;
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (-1);
	}
	width = ft_wdcounter(line, ' ');
	free(line);
	close(fd);
	return (width);
}

/*
 * Divide de line in numbers split by ' '
 */
void	fill_matrix(int *z_line, char *line)
{
	char	**nums;
	int		i;

	nums = ft_split(line, ' ');
	i = 0;
	while (nums[i])
	{
		z_line[i] = ft_atoi(nums[i]);
		free(nums[i]);
		i++;
	}
	free(nums);
}

/*
 *	1. Get de height and width of the map
 *	2. Assign memory in heap
 *	3. Fill the matrix
 */
void	read_file(char *file_name, t_fdf *data)
{
	int		fd;
	int		i;
	char	*line;

	data->height = get_height(file_name);
	data->width = get_width(file_name);
	if (data->height <= 0 || data->width <= 0)
		return ;
	data->z_matrix = (int **)malloc(sizeof(int *) * data->height);
	i = 0;
	while (i < data->height)
		data->z_matrix[i++] = (int *)malloc(sizeof(int) * data->width);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return ;
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		fill_matrix(data->z_matrix[i], line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
}
