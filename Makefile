NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3

MLX_DIR		= minilibx_opengl_20191021
INCLUDES	= -Iincludes -I$(MLX_DIR) -Ilibft
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

MLX_LIB		= $(MLX_DIR)/libmlx.a

SRC_DIR		= src/
SRC			:= $(shell find $(SRC_DIR) -mindepth 2 -type f -name "*.c" | sed "s|^$(SRC_DIR)||")
				
OBJ_DIR		= obj
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP			= $(OBJ:.o=.d)

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	$(CC) $(OBJ) -Llibft -lft $(MLX_FLAGS) -o $@

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -Ilibft -MMD -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

bonus : all

clean:
	@make clean -C libft
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(MLX_DIR) clean
fclean: clean
	@make fclean -C libft
	rm -f $(NAME)

re: fclean all

libft:
	make -C libft

-include $(DEP)

.PHONY: all clean fclean re