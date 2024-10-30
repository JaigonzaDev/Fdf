# Executable name
NAME = fdf 

# PATH directories
BIN_PATH = ./bin
SRC_PATH = ./src
INCLUDE_PATH = ./include
BUILD_PATH = ./build
LIB_PATH = ./lib

# Libraries
LIBFT = Libft
GNL = Get_next_line
PRINTF = Ft_printf
MLX = minilibx-linux

# External library path for libft
LIBFT_PATH = $(LIB_PATH)/$(LIBFT)
LIBFT_LIB = $(LIBFT_PATH)/lib/$(LIBFT)

# External library path for Ft_printf
PRINTF_PATH = $(LIB_PATH)/$(PRINTF)
PRINTF_LIB = $(PRINTF_PATH)/lib/libftprintf.a

# External library path for Get_next_line
GNL_PATH = $(LIB_PATH)/$(GNL)
GNL_LIB = $(GNL_PATH)/lib/libget_next_line.a

# External library path for MiniLibX
MLX_PATH = $(LIB_PATH)/$(MLX)
MLX_LIB = $(MLX_PATH)/libmlx.a

# Source paths
SRC_OBLIGATORY_PATH = $(SRC_PATH)/Obligatory
SRC_BONUS_PATH = $(SRC_PATH)/Bonus

# Build paths
OBLIGATORY_BUILD_PATH = $(BUILD_PATH)/Obligatory
BONUS_BUILD_PATH = $(BUILD_PATH)/Bonus

# .h files
INCLUDE_FILES_OBLIGATORY = fdf.h
INCLUDE_FILES_BONUS = fdf_bonus.h

# Include path and files
INCLUDE_PATH_FILES_OBLIGATORY = $(INCLUDE_PATH)/$(INCLUDE_FILES_OBLIGATORY)
INCLUDE_PATH_FILES_BONUS = $(INCLUDE_PATH)/$(INCLUDE_FILES_BONUS)

# All includes (includes libft and ft_printf)
ALL_INCLUDES = -I $(INCLUDE_PATH) -I $(LIBFT_PATH)/include -I $(GNL_PATH)/include -I $(PRINTF_PATH)/include -I $(MLX_PATH)

# .c files (without path)
C_FILES_OBLIGATORY = fdf.c read_file.c draw.c draw_utils.c draw_line_utils.c alg_utils.c read_file_utils.c
C_FILES_BONUS = fdf_bonus.c read_file_bonus.c draw_bonus.c draw_utils_bonus.c draw_line_utils_bonus.c alg_utils_bonus.c keys_bonus.c read_file_utils_bonus.c

# .c files with path
SRCS_OBLIGATORY = $(addprefix $(SRC_OBLIGATORY_PATH)/, $(C_FILES_OBLIGATORY))
SRCS_BONUS = $(addprefix $(SRC_BONUS_PATH)/, $(C_FILES_BONUS))

# Convert .c files to .o
OBJS_OBLIGATORY = $(patsubst $(SRC_OBLIGATORY_PATH)/%.c, $(OBLIGATORY_BUILD_PATH)/%.o, $(SRCS_OBLIGATORY))
OBJS_BONUS = $(patsubst $(SRC_BONUS_PATH)/%.c, $(BONUS_BUILD_PATH)/%.o, $(SRCS_BONUS))

# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
AR = ar -rcs
RM = rm -rf

# External libraries (libft, get_next_line, ft_printf, minilibx)
LIBS = -L$(LIBFT_PATH)/lib/Libft -L$(GNL_PATH)/lib -L$(PRINTF_PATH)/lib -L$(MLX_PATH) -lm -lft -lget_next_line -lftprintf -lmlx -lXext -lX11 -lm -lz

# Main rules
all: libft printf get_next_line minilibx $(NAME)

# Rule for the external libft library
libft:
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFT_PATH)

# Rule for the external ft_printf library
printf:
	@echo "Building ft_printf..."
	@$(MAKE) -C $(PRINTF_PATH)

# Rule for the external Gnl library
get_next_line:
	@echo "Building GNL..."
	@$(MAKE) -C $(GNL_PATH)

# Rule for the external MiniLibX library
minilibx:
	@echo "Building MiniLibX..."
	@$(MAKE) -C $(MLX_PATH)

# Compilation
$(NAME): $(OBJS_OBLIGATORY) $(LIBFT_LIB) $(GNL_LIB) $(PRINTF_LIB) $(MLX_LIB)
	@echo "Building $(NAME)..."
	@mkdir -p $(BIN_PATH)/Obligatory
	@$(CC) $(CFLAGS) $(OBJS_OBLIGATORY) $(LIBS) -o $(BIN_PATH)/Obligatory/$(NAME)
	@echo "$(NAME) built successfully."

# Rule to compile obligatory object files
$(OBLIGATORY_BUILD_PATH)/%.o: $(SRC_OBLIGATORY_PATH)/%.c $(INCLUDE_PATH_FILES_OBLIGATORY)
	@mkdir -p $(OBLIGATORY_BUILD_PATH)
	$(CC) $(CFLAGS) $(ALL_INCLUDES) -c $< -o $@

# Rule to compile bonus object files
bonus: libft printf get_next_line minilibx $(OBJS_BONUS)
	@echo "Building bonus..."
	@mkdir -p $(BIN_PATH)/Bonus
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBS) -o $(BIN_PATH)/Bonus/$(NAME)
	@echo "Bonus built successfully."

$(BONUS_BUILD_PATH)/%.o: $(SRC_BONUS_PATH)/%.c $(INCLUDE_PATH_FILES_BONUS)
	@mkdir -p $(BONUS_BUILD_PATH)
	$(CC) $(CFLAGS) $(ALL_INCLUDES) -c $< -o $@

# Clean files
clean:
	@$(RM) $(BUILD_PATH)
	@echo "Cleaned build files."

# Clean everything, including libft, gnl, ft_printf, and minilibx
fclean: clean
	@$(RM) $(BIN_PATH)
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@$(MAKE) -C $(GNL_PATH) fclean
	@$(MAKE) -C $(PRINTF_PATH) fclean
	@$(MAKE) -C $(MLX_PATH) clean
	@echo "Cleaned all files."

# Rebuild everything
re: fclean all

# PHONY rule
.PHONY: all clean fclean re bonus libft get_next_line printf minilibx
