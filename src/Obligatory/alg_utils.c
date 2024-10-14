/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:14:39 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/13 22:06:12 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 *  Isometric projection formula:
 *  'x = x - y * cos(angle)'
 *  'y = x + y * sin(angle) - z'
 */
void	isometric(float *x, float *y, int z, t_fdf *data)
{
	float	previous_x;
	float	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.8);
	*y = (previous_x + previous_y) * sin(0.5) - (z * data->z_cheat);
}

/*
 *  Adjusts the position of the points by shifting according to data offsets
 */
void	data_shift(t_fpoint *fp, t_fdf *data)
{
	fp->x0 += data->shift_x;
	fp->x1 += data->shift_x;
	fp->y0 += data->shift_y;
	fp->y1 += data->shift_y;
}

/*
 *  Adjusts the zoom of the points
 */
void	data_zoom(t_fpoint *fp, t_fdf *data)
{
	fp->x0 *= data->zoom;
	fp->y0 *= data->zoom;
	fp->x1 *= data->zoom;
	fp->y1 *= data->zoom;
}

void	draw_line(t_fpoint *fp, t_fdf *data)
{
	if (mod(fp->y1 - fp->y0) < mod(fp->x1 - fp->x0))
	{
		check_and_swap(fp, 1);
		calculate_gradient(fp, 1);
		draw_horizontal_line(fp, data);
	}
	else
	{
		check_and_swap(fp, 0);
		calculate_gradient(fp, 0);
		draw_vertical_line(fp, data);
	}
}
