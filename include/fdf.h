#ifndef FDF_H
# define FDF_H

#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "mlx.h"

typedef struct
{
	int width;
	int height;
	int **z_matrix;
	int zoom;
	int shift_x;
	int shift_y;
	int color;

	void *mlx_ptr;
	void *win_ptr;
} fdf;

void read_file(char *file_name, fdf *data);
void bresenham(float x, float y, float x1, float y1, fdf *data);
void draw(fdf *data);
#endif

