/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:19:35 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/15 12:15:48 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_horizontal_line(t_fpoint *fp, t_fdf *data)
{
	float	x;
	float	y;
	int		ix;
	int		iy;

	x = fp->x0;
	y = fp->y0;
	while (x <= fp->x1)
	{
		ix = (int)x;
		iy = (int)y;
		draw_pixels(data, ix, iy);
		x++;
		y += fp->utils.gradient;
	}
}

void	draw_vertical_line(t_fpoint *fp, t_fdf *data)
{
	float	x;
	float	y;
	int		ix;
	int		iy;

	x = fp->x0;
	y = fp->y0;
	while (y <= fp->y1)
	{
		ix = (int)x;
		iy = (int)y;
		draw_pixels(data, ix, iy);
		y++;
		x += fp->utils.gradient;
	}
}

void	check_and_swap(t_fpoint *fp, int flag_x)
{
	if (flag_x)
	{
		if (fp->x1 < fp->x0)
		{
			ft_swap(&fp->x0, &fp->x1);
			ft_swap(&fp->y0, &fp->y1);
		}
	}
	else
	{
		if (fp->y1 < fp->y0)
		{
			ft_swap(&fp->x0, &fp->x1);
			ft_swap(&fp->y0, &fp->y1);
		}
	}
}

void	calculate_gradient(t_fpoint *fp, int flag_x)
{
	slope(fp);
	if (flag_x)
		fp->utils.gradient = fp->utils.dy / fp->utils.dx;
	else
		fp->utils.gradient = fp->utils.dx / fp->utils.dy;
}
