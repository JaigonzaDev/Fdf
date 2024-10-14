/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:43:12 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/14 17:56:34 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/*
 *------------------------------------------
 *	Trigger function to close(x) event
 *------------------------------------------
 */
int	close_window_bonus(void *param)
{
	(void)param;
	exit(0);
}

/*------------------------------------------
 * 	Deal function for keys hooks:
 *------------------------------------------
 *	126 -> Up Arrow
 *	125 -> Down Arrow
 *	124 -> Left Arrow
 *	123 -> Right Arrow
 *	30 -> +
 *	44 -> -
 *	53 -> Esc
 *	38 -> j
 *	40 -> k
 *	37 -> h
 *		4 -> l
 *------------------------------------------
 */

int	deal_key_bonus(int key, t_fdfb *data)
{
	ft_printf("%d\n", key);
	if (key == 126)
		data->shift_y -= 10;
	else if (key == 125)
		data->shift_y += 10;
	else if (key == 123)
		data->shift_x -= 10;
	else if (key == 124)
		data->shift_x += 10;
	else if (key == 30)
		data->zoom += 1;
	else if (key == 44)
		data->zoom -= 1;
	else if (key == 53)
		exit(0);
	else if (key == 38)
		data->angle += 10;
	else if (key == 40)
		data->angle -= 10;
	else if (key == 37)
		data->focal_length += 10;
	else if (key == 4)
		data->focal_length -= 10;
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
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 500, "FDF");
	data->zoom = 30;
	data->shift_x = 500;
	data->shift_y = 30;
	data->z_cheat = 8;
	data->focal_length = 100;
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
	mlx_hook(data->win_ptr, 17, 0, close_window_bonus, NULL);
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

	if (argc != 2)
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
