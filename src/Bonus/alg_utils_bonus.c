/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:12:49 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/15 11:55:53 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	rotate_point_bonus(float *x, float *y, float angle)
{
	float	x_new;
	float	y_new;
	float	rad;

	rad = angle * (PI / 180);
	x_new = *x * cos(rad) - *y * sin(rad);
	y_new = *x * sin(rad) + *y * cos(rad);
	*x = x_new;
	*y = y_new;
}

void	conic_projection_bonus(float *x, float *y, int z, t_fdfb *data)
{
	float	previous_x;
	float	previous_y;
	float	d;

	d = data->focal_length;
	if (d <= 0)
		d = 1;
	previous_x = *x;
	previous_y = *y;
	*x = previous_x / (1 + (float)z / d);
	*y = previous_y / (1 + (float)z / d);
}

/*
 *  Adjusts the position of the points by shifting according to data offsets
 */
void	data_shift_bonus(t_fpointb *fp, t_fdfb *data)
{
	fp->x0 += data->shift_x;
	fp->x1 += data->shift_x;
	fp->y0 += data->shift_y;
	fp->y1 += data->shift_y;
}

/*
 *  Adjusts the zoom of the points
 */
void	data_zoom_bonus(t_fpointb *fp, t_fdfb *data)
{
	fp->x0 *= data->zoom;
	fp->y0 *= data->zoom;
	fp->x1 *= data->zoom;
	fp->y1 *= data->zoom;
}

void	draw_line_bonus(t_fpointb *fp, t_fdfb *data)
{
	if (mod_bonus(fp->y1 - fp->y0) < mod_bonus(fp->x1 - fp->x0))
	{
		check_and_swap_bonus(fp, 1);
		calculate_gradient_bonus(fp, 1);
		draw_horizontal_line_bonus(fp, data);
	}
	else
	{
		check_and_swap_bonus(fp, 0);
		calculate_gradient_bonus(fp, 0);
		draw_vertical_line_bonus(fp, data);
	}
}
