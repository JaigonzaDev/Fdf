#include "fdf_bonus.h"
#include <math.h>
#include <mlx.h>

// Macro para obtener el máximo de dos números
#define MAX(a, b) (a > b ? a : b)

// Función para calcular el valor absoluto de un número
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

// Función para aplicar la proyección cónica
void conic(float *x, float *y, int z, float d)
{
    // Si la distancia 'd' es muy pequeña, el factor de proyección tiende a infinito.
    if (d - z == 0)
        return;

    float scale = d / (d - z);  // Factor de escala basado en la profundidad (z)

    *x *= scale;  // Ajustar la coordenada x según la profundidad
    *y *= scale;  // Ajustar la coordenada y según la profundidad
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

// Algoritmo de Bresenham para dibujar líneas entre dos puntos
void bresenham(float x, float y, float x1, float y1, fdf *data)
{
    float x_step;
    float y_step;
    int max;
    int z;
    int z1;

    // Obtener las alturas z de los puntos
    z = data->z_matrix[(int)y][(int)x];
    z1 = data->z_matrix[(int)y1][(int)x1];

    // Aplicar zoom
    data_zoom(&x, &y, &x1, &y1, data);
    int color_start = 0xBBFAFF;  // Color base (ej. azul claro para z = 0)
    int color_end = 0xfc0345;    // Color final (ej. rojo oscuro para z != 0)

    // Calcular los pasos en x e y
    x_step = x1 - x;
    y_step = y1 - y;

    // Aplicar la proyección cónica
    float d = 10;  // Distancia del observador al plano de proyección (puedes ajustarla)
    conic(&x, &y, z, d);       // Aplicar proyección al primer punto
    conic(&x1, &y1, z1, d);    // Aplicar proyección al segundo punto

    // Aplicar traslación
    data_shift(&x, &y, &x1, &y1, data);

    // Determinar el número de pasos en la línea
    max = MAX(mod(x_step), mod(y_step));
    x_step /= max;
    y_step /= max;

    // Dibujar la línea pixel a pixel utilizando un bucle `while`
    int i = 0;
    while (i < max)
    {
        // Calcular el factor de interpolación basado en la posición en la línea
        float factor = (float)i / max;

        // Interpolar el color entre z y z1
        int interpolated_color = interpolate_color(color_start, color_end, factor);

        mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int)x, (int)y, interpolated_color);
        x += x_step;
        y += y_step;
        i++;
    }
}

// Función para dibujar la matriz de puntos en la pantalla
void draw(fdf *data)
{
    int x;
    int y;

    // Bucle para recorrer la altura de la matriz
    y = 0;
    while (y < data->height)
    {
        x = 0;  // Resetear x en cada fila
        while (x < data->width)
        {
            if (x < data->width - 1)
            {
                bresenham(x, y, x + 1, y, data);  // Dibuja línea hacia la derecha
            }
            if (y < data->height - 1)
            {
                bresenham(x, y, x, y + 1, data);  // Dibuja línea hacia abajo
            }
            x++;  // Incrementar x
        }
        y++;  // Incrementar y
    }
}

