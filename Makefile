# Detect platform
OS := $(shell uname)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# Files
SRC = 	main.c hook_handler.c check_args.c validate_file.c \
		validate_map.c render_3d.c draw_minimap.c player_move.c \
		garbage_collection/gc.c garbage_collection/gc_utils.c
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
EXEC = cub3D

# Directories
SRCDIR = src
OBJDIR = obj

# MinilibX
ifeq ($(OS), Darwin) # macOS
	CFLAGS += -D__APPLE__
    # macOS MiniLibX setup
    MLX = minilibx_opengl_20191021
    MLX_LIB = $(addprefix $(MLX)/,libmlx.a)
    MLX_INC = -I $(MLX)
    MLX_LNK = -L $(MLX) -lmlx -framework OpenGL -framework AppKit
else # Linux
    # Linux MiniLibX setup
	MLX = minilibx-linux
	MLX_LIB = $(addprefix $(MLX)/,libmlx.a)
	MLX_INC = -I $(MLX)
	MLX_LNK = -L $(MLX) -l mlx -lXext -lX11
endif

# libft
LIBFT = libft
LIBFT_LIB = $(addprefix $(LIBFT)/,libft.a)
LIBFT_INC = -I $(LIBFT)

# Targets
all: $(LIBFT_LIB) $(MLX_LIB) $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(MLX_LNK) -o $(EXEC)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT) bonus

$(MLX_LIB):
	$(MAKE) -C $(MLX)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(MLX_INC) $(LIBFT_INC) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFT) clean
	$(MAKE) -C $(MLX) clean

fclean: clean
	rm -f $(EXEC)
	$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
