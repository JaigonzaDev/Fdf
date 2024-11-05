/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:04:22 by jaigonza          #+#    #+#             */
/*   Updated: 2024/11/05 21:04:44 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <math.h>

typedef struct s_fdf
{
	int			width;
	int			height;
	int			**z_matrix;
	int			zoom;
	int			shift_x;
	int			shift_y;
	int			z_cheat;

	void		*mlx_ptr;
	void		*win_ptr;
}				t_fdf;

typedef struct s_fputils
{
	float		dx;
	float		dy;
	float		gradient;
}				t_fputils;

typedef struct s_fpoint
{
	float		x0;
	float		x1;
	float		y0;
	float		y1;
	int			z0;
	int			z1;
	t_fputils	utils;
}				t_fpoint;

int				close_window(t_fdf *data);
int				deal_key(int key, t_fdf *data);
void			init_data(t_fdf *data);
void			manage_mlx(t_fdf *data);

int				ft_wdcounter(char *line, char key);
int				get_height(char *file_name);
int				get_width(char *file_name);
void			fill_matrix(int *z_line, char *line, int width);
void			read_file(char *file_name, t_fdf *data);

void			alg_xiolin_wu(t_fpoint fp, t_fdf *data);
void			draw_line_in_direction(t_fpoint *fp, t_fdf *data,
					int horizontal);
void			draw(t_fdf *data);

void			ft_swap(float *a, float *b);
float			mod(float i);
void			slope(t_fpoint *fp);
void			draw_pixels(t_fdf *data, int ix, int iy);

void			draw_horizontal_line(t_fpoint *fp, t_fdf *data);
void			draw_vertical_line(t_fpoint *fp, t_fdf *data);
void			check_and_swap(t_fpoint *fp, int flag_x);
void			calculate_gradient(t_fpoint *fp, int flag_x);

void			isometric(float *x, float *y, int z, t_fdf *data);
void			data_shift(t_fpoint *fp, t_fdf *data);
void			data_zoom(t_fpoint *fp, t_fdf *data);
void			draw_line(t_fpoint *fp, t_fdf *data);

void			free_matrix(int **matrix);
void			cleanup(t_fdf *data);
void			allocate_matrix(t_fdf *data);
void			fill_matrix_from_file(int fd, t_fdf *data);
int				open_file(char *file_name);
#endif
