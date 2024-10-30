/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:11:10 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/29 17:16:33 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 *  Swap: swaps the values of a and b
 */
void	ft_swap(float *a, float *b)
{
	float	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/*
 *  Returns the absolute value of i
 */
float	mod(float i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}

void	slope(t_fpoint *fp)
{
	fp->utils.dx = fp->x1 - fp->x0;
	fp->utils.dy = fp->y1 - fp->y0;
}

void	draw_pixels(t_fdf *data, int ix, int iy)
{
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, ix, iy, 0xFFFF11);
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, ix, iy + 1, 0xFFFF11);
}
