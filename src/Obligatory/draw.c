#include "fdf.h"
#include <math.h>
#include <mlx.h>

// Macro corregida sin operador ternario
#define MAX(a, b) (a > b ? a : b)

// Función para calcular el valor absoluto de un número sin operador ternario
float mod(float i)
{
    if (i < 0)
    {
        return -i;
    }
    else
    {
        return i;
    }
}

// Función para aplicar la proyección isométrica
void isometric(float *x, float *y, int z)
{
    float previous_x = *x;
    float previous_y = *y;

    *x = (previous_x - previous_y) * cos(0.5);
    *y = (previous_x + previous_y) * sin(0.5) - z;
}

// Función para aplicar la traslación según los datos de desplazamiento
void data_shift(float *x, float *y, float *x1, float *y1, fdf *data)
{
    *x += data->shift_x;
    *y += data->shift_y;
    *x1 += data->shift_x;
    *y1 += data->shift_y;
}

// Función para aplicar el zoom
void data_zoom(float *x, float *y, float *x1, float *y1, fdf *data)
{
    *x *= data->zoom;
    *y *= data->zoom;
    *x1 *= data->zoom;
    *y1 *= data->zoom;
}

// Función para interpolar entre dos colores basados en un factor (0.0 a 1.0)
int interpolate_color(int start_color, int end_color, float factor)
{
    int r, g, b;
    int r1, g1, b1;
    int r2, g2, b2;

    // Extraer los componentes RGB de los colores
    r1 = (start_color >> 16) & 0xFF;
    g1 = (start_color >> 8) & 0xFF;
    b1 = start_color & 0xFF;

    r2 = (end_color >> 16) & 0xFF;
    g2 = (end_color >> 8) & 0xFF;
    b2 = end_color & 0xFF;

    // Interpolar los componentes
    r = (int)(r1 + factor * (r2 - r1));
    g = (int)(g1 + factor * (g2 - g1));
    b = (int)(b1 + factor * (b2 - b1));

    // Recombinar los componentes en un único valor RGB
    return (r << 16) | (g << 8) | b;
}

void alg_xiolin_wu(float x, float y, float x1, float y1, fdf *data)
{
    int i;
    float dx;
    float dy;
    int m;
    int z, z1;

    // Calcular los pasos en x e y
    dx = x1 - x;
    dy = y1 - y;
    m = dy / dx
    

    // Dibujar la línea pixel a pixel usando un bucle `while`
    i = 0;
    while (i <= m)
    {
	    x = x0 + i;
	    y = y0 + i * m;
    }


    // Obtener las alturas z de los puntos
    z = data->z_matrix[(int)y][(int)x];
    z1 = data->z_matrix[(int)y1][(int)x1];

    // Aplicar zoom
    data_zoom(&x, &y, &x1, &y1, data);

    // Definir colores de inicio y final del degradado
    int color_start = 0xBBFAFF;  // Color base (ej. azul claro para z = 0)
    int color_end = 0xfc0345;    // Color final (ej. rojo oscuro para z != 0)


    // Convertir a isométrico
    isometric(&x, &y, z);
    isometric(&x1, &y1, z1);

    // Aplicar traslación
    data_shift(&x, &y, &x1, &y1, data);

    // Determinar el número de pasos en la línea
    m = MAX(mod(x_step), mod(y_step));
    dx /= max;
    dy /= max;
}


// Función para dibujar la matriz de puntos en la pantalla usando bucles `while`
void draw(fdf *data)
{
    int x = 0;
    int y = 0;

    while (y < data->height)
    {
        x = 0;
        while (x < data->width)
        {
            if (x < data->width - 1)
            {
                alg_xiolin_wu(x, y, x + 1, y, data);
            }
            if (y < data->height - 1)
            {
                alg_xiolin_wu(x, y, x, y + 1, data);
            }
            x++;
        }
        y++;
    }
}

