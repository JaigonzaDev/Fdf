/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:43:20 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/14 17:56:36 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/*
 *  1. Set points values
 *  2. Apply isometric perspective
 *  3. Xiaolin Wu's algorithm for antialiasing lines
 */
void	alg_xiolin_wu_bonus(t_fpointb fp, t_fdfb *data)
{
	rotate_point_bonus(&fp.x0, &fp.y0, data->angle);
	rotate_point_bonus(&fp.x1, &fp.y1, data->angle);
	data_zoom_bonus(&fp, data);
	data_shift_bonus(&fp, data);
	conic_projection_bonus(&fp.x0, &fp.y0, fp.z0, data);
	conic_projection_bonus(&fp.x1, &fp.y1, fp.z1, data);
	draw_line_bonus(&fp, data);
}

void	draw_line_in_direction_bonus(t_fpointb *fp, t_fdfb *data,
		int horizontal)
{
	if (horizontal)
	{
		fp->z1 = data->z_matrix[(int)fp->y0][(int)fp->x0 + 1];
		fp->x1 = fp->x0 + 1;
		fp->y1 = fp->y0;
	}
	else
	{
		fp->z1 = data->z_matrix[(int)fp->y0 + 1][(int)fp->x0];
		fp->x1 = fp->x0;
		fp->y1 = fp->y0 + 1;
	}
	alg_xiolin_wu_bonus(*fp, data);
}

/*
 *	Draw pixels line x line
 */
void	draw_bonus(t_fdfb *data)
{
	t_fpointb	fp;

	fp.y0 = 0;
	while (fp.y0 < data->height)
	{
		fp.x0 = 0;
		while (fp.x0 < data->width)
		{
			fp.z0 = data->z_matrix[(int)fp.y0][(int)fp.x0];
			if (fp.x0 < data->width - 1)
				draw_line_in_direction_bonus(&fp, data, 1);
			if (fp.y0 < data->height - 1)
				draw_line_in_direction_bonus(&fp, data, 0);
			fp.x0++;
		}
		fp.y0++;
	}
}
