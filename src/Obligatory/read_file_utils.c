/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:32:22 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/30 15:30:03 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_matrix(int **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void	cleanup(t_fdf *data)
{
	if (!data)
		return ;
	if (data->z_matrix)
	{
		free_matrix(data->z_matrix);
		data->z_matrix = NULL;
	}
	if (data->mlx_ptr)
	{
		if (data->win_ptr)
		{
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
			data->win_ptr = NULL;
		}
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		data->mlx_ptr = NULL;
	}
}

void	allocate_matrix(t_fdf *data)
{
	int		i;

	data->z_matrix = (int **)malloc(sizeof(int *) * (data->height + 1));
	if (data->z_matrix == NULL)
		return ;
	data->z_matrix[data->height] = NULL;
	i = 0;
	while (i < data->height)
	{
		data->z_matrix[i] = (int *)malloc(sizeof(int) * data->width);
		if (data->z_matrix[i] == NULL)
		{
			free_matrix(data->z_matrix);
			return ;
		}
		i++;
	}
}

void	fill_matrix_from_file(int fd, t_fdf *data)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		fill_matrix(data->z_matrix[i], line, data->width);
		free(line);
		line = get_next_line(fd);
		i++;
	}
}

int	open_file(char *file_name)
{
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		return (-1);
	}
	return (fd);
}
