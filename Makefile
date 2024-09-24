# Nombre de los ejecutables
NAME = fdf 

# Directorios PATH
BIN_PATH = ./bin
SRC_PATH = ./src
INCLUDE_PATH = ./include
BUILD_PATH = ./build
LIB_PATH = ./lib

# Librerías
LIBFT = Libft
GNL = Get_next_line
PRINTF = Ft_printf
MLX = minilibx-linux

# Librería path externa libft
LIBFT_PATH = $(LIB_PATH)/$(LIBFT)
LIBFT_LIB = $(LIBFT_PATH)/lib/$(LIBFT)

# Librería path externa Ft_printf
PRINTF_PATH = $(LIB_PATH)/$(PRINTF)
PRINTF_LIB = $(PRINTF_PATH)/lib/libftprintf.a

# Librería path externa Get_next_line 
GNL_PATH = $(LIB_PATH)/$(GNL)
GNL_LIB = $(GNL_PATH)/lib/libget_next_line.a

# Librería path externa MiniLibX
MLX_PATH = $(LIB_PATH)/$(MLX)
MLX_LIB = $(MLX_PATH)/libmlx.a

# Paths de fuentes
SRC_OBLIGATORY_PATH = $(SRC_PATH)/Obligatory
SRC_BONUS_PATH = $(SRC_PATH)/Bonus

# Build Paths
OBLIGATORY_BUILD_PATH = $(BUILD_PATH)/Obligatory
BONUS_BUILD_PATH = $(BUILD_PATH)/Bonus

# Archivos .h
INCLUDE_FILES_OBLIGATORY = fdf.h

# Include Path and Files
INCLUDE_PATH_FILES_OBLIGATORY = $(INCLUDE_PATH)/$(INCLUDE_FILES_OBLIGATORY)

# Todos los includes (incluye libft y ft_printf)
ALL_INCLUDES = -I $(INCLUDE_PATH) -I $(LIBFT_PATH)/include -I $(GNL_PATH)/include -I $(PRINTF_PATH)/include -I $(MLX_PATH)

# Archivos .c (sin path)
C_FILES_OBLIGATORY = fdf.c read_file.c draw.c 
C_FILES_BONUS = fdf_bonus.c read_file_bonus.c draw_bonus.c 

# Archivos .c con path
SRCS_OBLIGATORY = $(addprefix $(SRC_OBLIGATORY_PATH)/, $(C_FILES_OBLIGATORY))
SRCS_BONUS = $(addprefix $(SRC_BONUS_PATH)/, $(C_FILES_BONUS))

# Conversión de archivos .c a .o
OBJS_OBLIGATORY = $(patsubst $(SRC_OBLIGATORY_PATH)/%.c, $(OBLIGATORY_BUILD_PATH)/%.o, $(SRCS_OBLIGATORY))
OBJS_BONUS = $(patsubst $(SRC_BONUS_PATH)/%.c, $(BONUS_BUILD_PATH)/%.o, $(SRCS_BONUS))

# Compilador y flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
AR = ar -rcs
RM = rm -rf

# Librerías externas (libft, get_next_line, ft_printf, minilibx)
LIBS = -L$(LIBFT_PATH)/lib/Libft -L$(GNL_PATH)/lib -L$(PRINTF_PATH)/lib -L$(MLX_PATH) -lm -lft -lget_next_line -lftprintf -lmlx -lXext -lX11

# Reglas principales
all: libft printf get_next_line minilibx $(NAME)

# Regla para la librería externa libft
libft:
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFT_PATH)

# Regla para la librería externa ft_printf
printf:
	@echo "Building ft_printf..."
	@$(MAKE) -C $(PRINTF_PATH)

# Regla para la librería externa Gnl 
get_next_line:
	@echo "Building GNL..."
	@$(MAKE) -C $(GNL_PATH)

# Regla para la librería externa MiniLibX
minilibx:
	@echo "Building MiniLibX..."
	@$(MAKE) -C $(MLX_PATH)

# Compilación
$(NAME): $(OBJS_OBLIGATORY) $(LIBFT_LIB) $(GNL_LIB) $(PRINTF_LIB) $(MLX_LIB)
	@echo "Building $(NAME)..."
	@mkdir -p $(BIN_PATH)/Obligatory
	@$(CC) $(CFLAGS) $(OBJS_OBLIGATORY) $(LIBS) -o $(BIN_PATH)/Obligatory/$(NAME)
	@echo "$(NAME) built successfully."

# Regla para compilar los archivos objeto obligatorios
$(OBLIGATORY_BUILD_PATH)/%.o: $(SRC_OBLIGATORY_PATH)/%.c $(INCLUDE_PATH_FILES_OBLIGATORY)
	@mkdir -p $(OBLIGATORY_BUILD_PATH)
	$(CC) $(CFLAGS) $(ALL_INCLUDES) -c $< -o $@

# Regla para compilar los archivos objeto bonus
bonus: libft printf get_next_line minilibx $(OBJS_BONUS)
	@echo "Building bonus..."
	@mkdir -p $(BIN_PATH)/Bonus
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBS) -o $(BIN_PATH)/Bonus/$(NAME)
	@echo "Bonus built successfully."

$(BONUS_BUILD_PATH)/%.o: $(SRC_BONUS_PATH)/%.c $(INCLUDE_PATH_FILES_OBLIGATORY)
	@mkdir -p $(BONUS_BUILD_PATH)
	$(CC) $(CFLAGS) $(ALL_INCLUDES) -c $< -o $@

# Limpiar archivos
clean:
	@$(RM) $(BUILD_PATH)
	@echo "Cleaned build files."

# Limpiar todo, incluyendo libft, gnl, ft_printf y minilibx
fclean: clean
	@$(RM) $(BIN_PATH)
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@$(MAKE) -C $(GNL_PATH) fclean
	@$(MAKE) -C $(PRINTF_PATH) fclean
	@$(MAKE) -C $(MLX_PATH) clean
	@echo "Cleaned all files."

# Volver a compilar todo
re: fclean all

# Regla de PHONY
.PHONY: all clean fclean re bonus libft get_next_line printf minilibx

