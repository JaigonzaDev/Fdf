/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:23:25 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/14 17:22:18 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/*
 *  1. Set points values
 *  2. Apply isometric perspective
 *  3. Xiaolin Wu's algorithm for antialiasing lines
 */
void	alg_xiolin_wu(t_fpoint fp, t_fdf *data)
{
	data_zoom(&fp, data);
	data_shift(&fp, data);
	isometric(&fp.x0, &fp.y0, fp.z0, data);
	isometric(&fp.x1, &fp.y1, fp.z1, data);
	draw_line(&fp, data);
}

void	draw_line_in_direction(t_fpoint *fp, t_fdf *data, int horizontal)
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
	alg_xiolin_wu(*fp, data);
}

/*
 *  Draw lines for the whole matrix, connecting adjacent points
 */
void	draw(t_fdf *data)
{
	t_fpoint	fp;

	fp.y0 = 0;
	while (fp.y0 < data->height)
	{
		fp.x0 = 0;
		while (fp.x0 < data->width)
		{
			fp.z0 = data->z_matrix[(int)fp.y0][(int)fp.x0];
			if (fp.x0 < data->width - 1)
				draw_line_in_direction(&fp, data, 1);
			if (fp.y0 < data->height - 1)
				draw_line_in_direction(&fp, data, 0);
			fp.x0++;
		}
		fp.y0++;
	}
}
