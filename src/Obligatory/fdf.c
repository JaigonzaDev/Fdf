#include "fdf.h"

/*
 *------------------------------------------
 *	Trigger function to close(x) event
 *------------------------------------------
 */
int close_window(void *param)
{
    (void)param;
    exit(0);
}

/*------------------------------------------
 * 	Deal function for keys hooks:
 *------------------------------------------
 *	126 -> Up Arrow
 *	125 -> Down Arrow
 *	124 -> Left Arrow
 *	123 -> Right Arrow
 *	30 -> +
 *	44 -> -
 *	53 -> Esc
 *------------------------------------------
 */
int deal_key(int key, fdf *data)
{
    if (key == 126)
        data->shift_y -= 10;
    else if (key == 125)
        data->shift_y += 10;
    else if (key == 123)
        data->shift_x -= 10;
    else if (key == 124)
        data->shift_x += 10;
    else if (key == 30)
        data->zoom += 1;
    else if (key == 44)
        data->zoom -= 1;
    else if (key == 53)
        exit(0);
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    draw(data);
    return (0);
}

/*
 *------------------------------------------
 *	Init struct t_fdf
 *------------------------------------------
 */
void init_data(fdf *data)
{
    data = (fdf *)malloc(sizeof(fdf));
    if (!data)
    {
        ft_printf("Error: Memory allocation failed\n");
        return (1);
    }
    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 500, "FDF");
    data->zoom = 30;
    data->shift_x = 500;
    data->shift_y = 30;
    data->z_cheat = 8;
}

/*
 *------------------------------------------
 *	Press x to close
 *	Deal Keys
 *	Loop waiting for events
 *------------------------------------------
 */
void manage_mlx(fdf *data)
{
    mlx_hook(data->win_ptr, 17, 0, close_window, NULL);    
    mlx_key_hook(data->win_ptr, deal_key, data);
    mlx_loop(data->mlx_ptr);
}

/*
 *------------------------------------------
 *	Check number of args
 *------------------------------------------
 */
int check_data (int argc, char **argv)
{
    if (argc != 2)
    {
        ft_printf("Usage: %s <map_file>\n", argv[0]);
        return (0);
    }
    return (1);
}

/*
 *------------------------------------------
 *	1. Check arguments
 *	2. Init Fdf struct
 *	3. Put de map in matrix
 *	4. Draw de map (line alg - put pixel - isometric view)
 *	5. Manage mlx (hooks, loop) 
 *------------------------------------------
 */
int main(int argc, char **argv)
{
    fdf *data;

    check_data(argc, argv);
    init_data(data);
    read_file(argv[1], data);
    draw(data);
    manage_mlx(data);
    return (0);
}
