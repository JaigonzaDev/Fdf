/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:14:28 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/15 12:08:34 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/*
 *  Swap: swaps the values of a and b
 */
void	ft_swap_bonus(float *a, float *b)
{
	float	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/*
 *  Returns the absolute value of i
 */
float	mod_bonus(float i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}

void	slope_bonus(t_fpointb *fp)
{
	fp->utils.dx = fp->x1 - fp->x0;
	fp->utils.dy = fp->y1 - fp->y0;
}

void	draw_pixels_bonus(t_fdfb *data, int ix, int iy)
{
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, ix, iy, 0xFFFF11);
}
