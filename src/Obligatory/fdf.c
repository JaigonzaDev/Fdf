/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:23:37 by jaigonza          #+#    #+#             */
/*   Updated: 2024/11/05 21:22:28 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 *------------------------------------------
 *	Trigger function to close(x) event
 *------------------------------------------
 */
int	close_window(t_fdf *data)
{
	cleanup(data);
	exit(0);
}

/*------------------------------------------
 * 	Deal function for keys hooks (Linux):
 *------------------------------------------
 *	65362 -> Up Arrow
 *	65364 -> Down Arrow
 *	65361 -> Left Arrow
 *	65363 -> Right Arrow
 *	43 -> +
 *	45 -> -
 *	65307 -> Esc
 *------------------------------------------
 */
int	deal_key(int key, t_fdf *data)
{
	if (key == 65362)
		data->shift_y -= 10;
	else if (key == 65364)
		data->shift_y += 10;
	else if (key == 65361)
		data->shift_x -= 10;
	else if (key == 65363)
		data->shift_x += 10;
	else if (key == 43)
		data->zoom += 1;
	else if (key == 45)
		data->zoom -= 1;
	else if (key == 65307)
	{
		cleanup(data);
		exit(0);
	}
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
	return (0);
}

/*
 *------------------------------------------
 *	Init struct t_fdf
 *------------------------------------------
 */
void	init_data(t_fdf *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 2000, 1000, "FDF");
	data->zoom = 30;
	data->shift_x = 500;
	data->shift_y = 30;
	data->z_cheat = 8;
}

/*
 *------------------------------------------
 *	Press x to close
 *	Deal Keys
 *	Loop waiting for events
 *------------------------------------------
 */
void	manage_mlx(t_fdf *data)
{
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	mlx_key_hook(data->win_ptr, deal_key, data);
	mlx_loop(data->mlx_ptr);
}

/*
 *------------------------------------------
 *	1. Check arguments
 *	2. Init Fdf struct
 *	3. Put de map in matrix
 *	4. Draw de map (line alg - put pixel - isometric view)
 *	5. Manage mlx (hooks, loop)
 *------------------------------------------
 */
int	main(int argc, char **argv)
{
	t_fdf	data;

	if (argc != 2 || open_file(argv[1]) == -1)
	{
		ft_printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	init_data(&data);
	read_file(argv[1], &data);
	draw(&data);
	manage_mlx(&data);
	cleanup(&data);
	return (0);
}
