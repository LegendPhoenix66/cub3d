# Detect platform
OS := $(shell uname)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# Files
SRC = 	main.c hook_handler.c check_args.c player_move.c composite_frame.c \
		validate/validate_map.c validate/color_processing.c validate/content_validation.c \
		validate/file_init.c validate/file_reader.c validate/file_utils.c validate/texture_processing.c \
		validate/game_utils.c validate/map_processing.c validate/map_validation.c \
		render/ray_init.c render/stripe_calc.c render/stripe_draw.c render/render_3d.c \
		minimap/draw_minimap.c minimap/draw_minimap_utils.c minimap/draw_minimap_tiles.c \
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
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(MLX_LNK) -lm -o $(EXEC)

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
