#include "fdf_bonus.h"

#include "fdf.h"
#include <mlx.h>
#include <stdio.h>

int deal_key(int key, fdf *data)
{
    ft_printf("%d\n", key);
    if (key == 126) // Flecha arriba
        data->shift_y -= 10;
    else if (key == 125) // Flecha abajo
        data->shift_y += 10;
    else if (key == 123) // Flecha izquierda
        data->shift_x -= 10;
    else if (key == 124) // Flecha derecha
        data->shift_x += 10;
    else if (key == 24) // Zoom in (mayúsculas)
        data->zoom += 1;
    else if (key == 27) // Zoom out (menos)
        data->zoom -= 1;
    else if (key == 53) // ESC
        exit(0); // Salir del programa

    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    draw(data);
    return (0);
}

int main(int argc, char **argv)
{
    fdf *data;

    if (argc != 2)
    {
        ft_printf("Usage: %s <map_file>\n", argv[0]);
        return (1);
    }

    data = (fdf *)malloc(sizeof(fdf));
    if (!data)
    {
        ft_printf("Error: Memory allocation failed\n");
        return (1);
    }
    
    read_file(argv[1], data);
    
    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "FDF");
    data->zoom = 1;
    data->shift_x = 200;
    data->shift_y = 200;
    
    draw(data);
    mlx_key_hook(data->win_ptr, deal_key, data);
    mlx_loop(data->mlx_ptr);

    return (0);
}
