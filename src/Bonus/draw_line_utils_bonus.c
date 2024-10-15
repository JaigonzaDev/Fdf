/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:16:40 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/15 12:11:13 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	draw_horizontal_line_bonus(t_fpointb *fp, t_fdfb *data)
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
		draw_pixels_bonus(data, ix, iy);
		x++;
		y += fp->utils.gradient;
	}
}

void	draw_vertical_line_bonus(t_fpointb *fp, t_fdfb *data)
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
		draw_pixels_bonus(data, ix, iy);
		y++;
		x += fp->utils.gradient;
	}
}

void	check_and_swap_bonus(t_fpointb *fp, int flag_x)
{
	if (flag_x)
	{
		if (fp->x1 < fp->x0)
		{
			ft_swap_bonus(&fp->x0, &fp->x1);
			ft_swap_bonus(&fp->y0, &fp->y1);
		}
	}
	else
	{
		if (fp->y1 < fp->y0)
		{
			ft_swap_bonus(&fp->x0, &fp->x1);
			ft_swap_bonus(&fp->y0, &fp->y1);
		}
	}
}

void	calculate_gradient_bonus(t_fpointb *fp, int flag_x)
{
	slope_bonus(fp);
	if (flag_x)
		fp->utils.gradient = fp->utils.dy / fp->utils.dx;
	else
		fp->utils.gradient = fp->utils.dx / fp->utils.dy;
}
