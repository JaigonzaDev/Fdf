#include "fdf_bonus.h"

// Contador de palabras que evita espacios consecutivos
int ft_wdcounter(char *line, char key)
{
    int width = 0;
    int in_word = 0;

    while (*line)
    {
        if (*line != key && in_word == 0)
        {
            in_word = 1;
            width++;
        }
        else if (*line == key)
            in_word = 0;
        line++;
    }
    return width;
}

// Función para calcular la altura del archivo (número de líneas)
int get_height(char *file_name)
{
    char *line;
    int fd;
    int height;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return -1;
    height = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        height++;
        free(line);
    }
    close(fd);
    return height;
}

// Función para calcular el ancho (número de columnas)
int get_width(char *file_name)
{
    int width;
    int fd;
    char *line;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return -1;
    line = get_next_line(fd);
    if (!line)
    {
        close(fd);
        return -1;
    }
    width = ft_wdcounter(line, ' ');
    free(line);
    close(fd);
    return width;
}

// Función para llenar una fila de la matriz con los valores de la línea
void fill_matrix(int *z_line, char *line)
{
    char **nums;
    int i;

    nums = ft_split(line, ' ');
    i = 0;
    while (nums[i])
    {
        z_line[i] = ft_atoi(nums[i]);
        free(nums[i]);
        i++;
    }
    free(nums);
}

// Función para leer el archivo y llenar la matriz de alturas z
void read_file(char *file_name, fdf *data)
{
    int fd;
    int i;
    char *line;

    // Obtener altura y ancho del archivo
    data->height = get_height(file_name);
    data->width = get_width(file_name);

    // **Añadimos un printf para ver height y width**
    printf("Altura (height): %d\n", data->height);
    printf("Ancho (width): %d\n", data->width);

    if (data->height <= 0 || data->width <= 0)
    {
        printf("Error: archivo inválido\n");
        return;
    }

    // Reservar memoria para la matriz
    data->z_matrix = (int **)malloc(sizeof(int *) * data->height);
    i = 0;
    while (i < data->height)
        data->z_matrix[i++] = (int *)malloc(sizeof(int) * data->width);

    // Abrir el archivo y llenar la matriz
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
    {
        printf("Error: no se pudo abrir el archivo\n");
        return;
    }

    i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        fill_matrix(data->z_matrix[i], line);
        free(line);
        i++;
    }
    close(fd);
}

