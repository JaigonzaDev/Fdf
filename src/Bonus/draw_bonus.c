#include "fdf.h"
#include <math.h>
#include <mlx.h>

void rotate_point(float *x, float *y, float angle)
{
    float rad = angle * (M_PI / 180); // Convierte el ángulo a radianes
    float x_new = *x * cos(rad) - *y * sin(rad);
    float y_new = *x * sin(rad) + *y * cos(rad);
    *x = x_new;
    *y = y_new;
}

// Función para intercambiar dos variables flotantes
void ft_swap(float *a, float *b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

// Función para calcular el valor absoluto de un número
float mod(float i)
{
    if (i < 0)
        return -i;
    else
        return i;
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

void conic_projection(float *x, float *y, int z, fdf *data)
{
    // Distancia focal o punto de fuga (ajusta este valor según el efecto que desees)
    float d = data->focal_length; // Define el valor en tu estructura fdf, ej. 1000.0
    
    if (d <= 0)
	    d = 1.0;
    // Guarda las coordenadas originales
    float previous_x = *x;
    float previous_y = *y;

    // Aplica la proyección cónica
    *x = previous_x / (1 + (float)z / d);
    *y = previous_y / (1 + (float)z / d);
}

void alg_xiolin_wu(float x0, float y0, float x1, float y1, int z0, int z1, fdf *data)
{
    int ix, iy;             // Coordenadas enteras de los píxeles
    float dx, dy;           // Diferencias en x e y
    float gradient, dist;   // Gradiente (pendiente) y distancia para interpolar colores
    float x, y;             // Coordenadas actuales (con decimales)

    //rotate
    rotate_point(&x0, &y0, data->angle);
    rotate_point(&x1, &y1, data->angle);
    // Aplicar zoom y traslación
    data_zoom(&x0, &y0, &x1, &y1, data);

    // Proyección cónica
    conic_projection(&x0, &y0, z0, data);
    conic_projection(&x1, &y1, z1, data);

    // Aplicar traslación
    data_shift(&x0, &y0, &x1, &y1, data);

    // Si el cambio absoluto en y es menor que en x, dibujar horizontalmente
    if (fabs(y1 - y0) < fabs(x1 - x0))
    {
        // Asegurarse de que siempre dibujamos de izquierda a derecha
        if (x1 < x0)
        {
            ft_swap(&x0, &x1);
            ft_swap(&y0, &y1);
        }

        // Calcular las diferencias y el gradiente
        dx = x1 - x0;
        dy = y1 - y0;
        gradient = dy / dx;

        // Dibujar los puntos en el rango de x0 a x1
        x = x0;
        y = y0;

        while (x <= x1)
        {
            ix = (int)x;
            iy = (int)y;
            dist = y - iy;  // Distancia fraccional

            // Dibujar píxeles interpolando colores
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, ix, iy, (1 - dist) * 0xFFFF11);      // Píxel superior
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, ix, iy + 1, dist * 0xFFFF11 * data->z_cheat);        // Píxel inferior

            x++;         // Incrementar x en 1
            y += gradient;  // Incrementar y en función del gradiente
        }
    }
    // Si el cambio absoluto en y es mayor que en x, dibujar verticalmente
    else
    {
        // Asegurarse de que siempre dibujamos de abajo hacia arriba
        if (y1 < y0)
        {
            ft_swap(&x0, &x1);
            ft_swap(&y0, &y1);
        }

        // Calcular las diferencias y el gradiente
        dx = x1 - x0;
        dy = y1 - y0;
        gradient = dx / dy;

        // Dibujar los puntos en el rango de y0 a y1
        x = x0;
        y = y0;

        while (y <= y1)
        {
            ix = (int)x;
            iy = (int)y;
            dist = x - ix;  // Distancia fraccional

            // Dibujar píxeles interpolando colores
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, ix, iy, (1 - dist) * 0xFFFF11);      // Píxel izquierdo
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, ix + 1, iy, dist * 0xFFFFFF * data->z_cheat);        // Píxel derecho

            y += 1;         // Incrementar y en 1
            x += gradient;  // Incrementar x en función del gradiente
        }
    }
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
            int z = data->z_matrix[y][x];
            if (x < data->width - 1)
            {
                int z1 = data->z_matrix[y][x + 1];
                alg_xiolin_wu(x, y, x + 1, y, z, z1, data); // Dibuja línea horizontal
            }
            if (y < data->height - 1)
            {
                int z1 = data->z_matrix[y + 1][x];
                alg_xiolin_wu(x, y, x, y + 1, z, z1, data); // Dibuja línea vertical
            }
            x++;
        }
        y++;
    }
}


