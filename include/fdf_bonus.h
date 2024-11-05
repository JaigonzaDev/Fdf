/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:02:46 by jaigonza          #+#    #+#             */
/*   Updated: 2024/11/05 21:05:24 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "fdf.h"

# define PI 3.14159

typedef struct s_fdfb
{
	int			width;
	int			height;
	int			**z_matrix;
	int			zoom;
	int			shift_x;
	int			shift_y;
	int			focal_length;
	float		angle;

	void		*mlx_ptr;
	void		*win_ptr;
}				t_fdfb;

typedef struct s_fputilsb
{
	float		dx;
	float		dy;
	float		gradient;
}				t_fputilsb;

typedef struct s_fpointb
{
	float		x0;
	float		x1;
	float		y0;
	float		y1;
	int			z0;
	int			z1;
	t_fputilsb	utils;
}				t_fpointb;

void			draw_horizontal_line_bonus(t_fpointb *fp, t_fdfb *data);
void			draw_vertical_line_bonus(t_fpointb *fp, t_fdfb *data);
void			check_and_swap_bonus(t_fpointb *fp, int flag_x);
void			calculate_gradient_bonus(t_fpointb *fp, int flag_x);

int				open_file_bonus(char *file_name);
void			fill_matrix_bonus(int *z_line, char *line, int width);
void			fill_matrix_from_file_bonus(int fd, t_fdfb *data);
void			free_matrix_bonus(int **matrix);
void			allocate_matrix_bonus(t_fdfb *data);
int				ft_wdcounter_bonus(char *line, char key);
int				get_height_bonus(char *file_name);
int				get_width_bonus(char *file_name);
void			cleanup_bonus(t_fdfb *data);
void			read_file_bonus(char *file_name, t_fdfb *data);

void			ft_swap_bonus(float *a, float *b);
float			mod_bonus(float i);
void			slope_bonus(t_fpointb *fp);
void			draw_pixels_bonus(t_fdfb *data, int ix, int iy);

int				close_window_bonus(t_fdfb *data);
int				deal_key_bonus(int key, t_fdfb *data);
void			init_data_bonus(t_fdfb *data);
void			manage_mlx_bonus(t_fdfb *data);

void			rotate_point_bonus(float *x, float *y, float angle);
void			conic_projection_bonus(float *x, float *y, int z, t_fdfb *data);
void			data_shift_bonus(t_fpointb *fp, t_fdfb *data);
void			data_zoom_bonus(t_fpointb *fp, t_fdfb *data);
void			draw_line_bonus(t_fpointb *fp, t_fdfb *data);

void			alg_xiolin_wu_bonus(t_fpointb fp, t_fdfb *data);
void			draw_line_in_direction_bonus(t_fpointb *fp, t_fdfb *data,
					int horizontal);
void			draw_bonus(t_fdfb *data);

void			move_view(int key, t_fdfb *data);
void			zoom_view(int key, t_fdfb *data);
void			change_angle(int key, t_fdfb *data);
void			change_focal_length(int key, t_fdfb *data);

#endif
