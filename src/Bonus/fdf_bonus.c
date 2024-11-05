/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:43:12 by jaigonza          #+#    #+#             */
/*   Updated: 2024/11/05 21:24:06 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/*
 *------------------------------------------
 *	Trigger function to close(x) event
 *------------------------------------------
 */
int	close_window_bonus(t_fdfb *data)
{
	cleanup_bonus(data);
	exit(0);
}

/*------------------------------------------
 * 	Deal function for keys hooks:
 *------------------------------------------
 *	65307 -> Esc
 *------------------------------------------
 */
int	deal_key_bonus(int key, t_fdfb *data)
{
	move_view(key, data);
	zoom_view(key, data);
	change_angle(key, data);
	change_focal_length(key, data);
	if (key == 65307)
	{
		cleanup_bonus(data);
		exit(0);
	}
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw_bonus(data);
	return (0);
}

/*
 *------------------------------------------
 *	Init struct t_fdf
 *------------------------------------------
 */
void	init_data_bonus(t_fdfb *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 2000, 1000, "FDF");
	data->zoom = 30;
	data->shift_x = 600;
	data->shift_y = 600;
	data->focal_length = 10;
	data->angle = 200;
}

/*
 *------------------------------------------
 *	Press x to close
 *	Deal Keys
 *	Loop waiting for events
 *------------------------------------------
 */
void	manage_mlx_bonus(t_fdfb *data)
{
	mlx_hook(data->win_ptr, 17, 0, close_window_bonus, data);
	mlx_key_hook(data->win_ptr, deal_key_bonus, data);
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
	t_fdfb	data;

	if (argc != 2 || open_file_bonus(argv[1]) == -1)
	{
		ft_printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	init_data_bonus(&data);
	read_file_bonus(argv[1], &data);
	draw_bonus(&data);
	manage_mlx_bonus(&data);
	return (0);
}
