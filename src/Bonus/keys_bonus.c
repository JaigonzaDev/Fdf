/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:22:39 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/15 12:21:22 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/*
 *	65362 -> Up Arrow
 *	65364 -> Down Arrow
 *	65361 -> Left Arrow
 *	65362 -> Right Arrow
 */
void	move_view(int key, t_fdfb *data)
{
	if (key == 65362)
		data->shift_y -= 10;
	else if (key == 65364)
		data->shift_y += 10;
	else if (key == 65361)
		data->shift_x -= 10;
	else if (key == 65363)
		data->shift_x += 10;
}

/*
 *	43 -> +
 *	45 -> -
 */
void	zoom_view(int key, t_fdfb *data)
{
	if (key == 43)
		data->zoom += 1;
	else if (key == 45)
		data->zoom -= 1;
}

/*
 *	106 -> j
 *	107 -> k
 */
void	change_angle(int key, t_fdfb *data)
{
	if (key == 106)
		data->angle += 10;
	else if (key == 107)
		data->angle -= 10;
}

/*
 *	104 -> h
 *  108 -> l
 */
void	change_focal_length(int key, t_fdfb *data)
{
	if (key == 108)
		data->focal_length += 10;
	else if (key == 104)
		data->focal_length -= 10;
}
