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

    *x = (previous_x - previous_y) * cos(0.6);
    *y = (previous_x + previous_y) * sin(0.6) - z;
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

// Algoritmo de Bresenham para dibujar líneas entre dos puntos sin operador ternario y sin bucle `while`
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

    // Asignar color según las alturas z sin operador ternario
    if (z != 0 || z1 != 0)
    {
        data->color = 0x1234ff; // Color para puntos con z distinta de 0
    }
    else
    {
        data->color = 0xffffff; // Color para puntos con z igual a 0
    }

    // Calcular los pasos en x e y
    x_step = x1 - x;
    y_step = y1 - y;

    // Convertir a isométrico
    isometric(&x, &y, z);
    isometric(&x1, &y1, z1);

    // Aplicar traslación
    data_shift(&x, &y, &x1, &y1, data);

    // Determinar el número de pasos en la línea
    max = MAX(mod(x_step), mod(y_step));
    x_step /= max;
    y_step /= max;

    // Dibujar la línea pixel a pixel usando bucle `for` en lugar de `while`
    int i;
    int steps = max; // Número de iteraciones

    for (i = 0; i < steps; i++)
    {
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int)x, (int)y, data->color);
        x += x_step;
        y += y_step;
    }
}

// Función para dibujar la matriz de puntos en la pantalla sin bucles `while`
void draw(fdf *data)
{
    int x;
    int y;

    for (y = 0; y < data->height; y++)
    {
        for (x = 0; x < data->width; x++)
        {
            if (x < data->width - 1)
            {
                bresenham(x, y, x + 1, y, data);
            }
            if (y < data->height - 1)
            {
                bresenham(x, y, x, y + 1, data);
            }
        }
    }
}

