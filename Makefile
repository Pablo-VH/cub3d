# --------------------🎮 Configuración --------------------
NAME        := cub3D
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Ofast

# --------------------📁 Directorios --------------------
INC         := inc/
SRCS_DIR    := srcs/
OBJS_DIR    := objs/
LIBFT_DIR   := libft/
MLX_DIR     := MLX42/
MLX_BUILD   := $(MLX_DIR)/build

# --------------------📚 Includes y Librerías --------------------
INCLUDES    := -I$(INC) -I$(LIBFT_DIR)/inc -I$(MLX_DIR)/include/MLX42
LIBFT       := $(LIBFT_DIR)/libft.a
MLX_LIB     := $(MLX_BUILD)/libmlx42.a
LDFLAGS     := $(MLX_LIB) -ldl -lglfw -pthread -lm

# --------------------🧱 Archivos --------------------
SRCS_FILES  := main.c map_management.c parsing.c utils.c\
				colors_utils.c charge_elements_info.c execute_init.c\
				ft_print_screen.c img_init.c bonus.c
SRCS        := $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS        := $(addprefix $(OBJS_DIR)/, $(SRCS_FILES:.c=.o))

# --------------------🎯 Reglas --------------------
all: submodules $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	@echo "🎮 Compilando $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "🚀 ¡Compilado con éxito!"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "🛠️  Compilando $<"

$(LIBFT):
	@echo "📚 Compilando libft..."
	@make -C $(LIBFT_DIR)
	@echo "📘 libft compilado!"

$(MLX_LIB):
	@echo "🎨 Compilando MLX42..."
	@cmake -B $(MLX_BUILD) -S $(MLX_DIR) > /dev/null
	@cmake --build $(MLX_BUILD) > /dev/null
	@echo "🖼️  MLX42 compilado!"

submodules:
	@echo "🔄 Actualizando submódulos..."
	@git submodule init
	@git submodule update --remote
	@echo "✅ Submódulos actualizados."

clean:
	@rm -rf $(OBJS_DIR)
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(MLX_BUILD)
	@echo "🧹 Clean hecho!"

fclean: clean
	@rm -f $(NAME)
	@echo "🧼 Fclean completado!"

re: fclean all

.PHONY: all clean fclean re submodules
