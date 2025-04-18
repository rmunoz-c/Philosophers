# Nombre del ejecutable
NAME := philo

# Compilador y flags
CC = cc
CFLAGS := -Wall -Werror -Wextra -g -MMD -MP

# Rutas de fuentes y objetos
SRC :=	

BUILD_DIR := build
OBJ := $(SRC:.c=.o)
OBJ := $(addprefix $(BUILD_DIR)/, $(OBJ))
DEP := $(OBJ:.o=.d)

# Colores ANSI
BLUE := \033[34m
GREEN := \033[32m
YELLOW := \033[33m
CYAN := \033[36m
RESET := \033[0m

.DEFAULT_GOAL := all

all: $(NAME)
	@printf "$(GREEN)\n✅ Compilación completa$(RESET)\n"

$(NAME): $(OBJ)
	@printf "$(CYAN)\r🔗 Enlazando: $(NAME)                     $(RESET)\n"
	@$(CC) $(OBJ) -o $(NAME) $(CFLAGS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(BLUE)\r⚙️  Compilando: $<                         $(RESET)\n"
	@$(CC) $(CFLAGS) -o $@ -c $<

run: $(NAME)
	@printf "$(CYAN)\r🔜 Ejecutando: $(NAME)...                 $(RESET)\n"
	@./$(NAME)

clean:
	@printf "$(YELLOW)\r🧹 Limpiando objetos...                $(RESET)\n"
	@rm -rf $(BUILD_DIR)

fclean: clean
	@printf "$(YELLOW)\r🗑️  Borrando ejecutable...              $(RESET)\n"
	@rm -f $(NAME)
	@printf "$(GREEN)\r✅  Limpieza completa.                  $(RESET)\n"

re: fclean all

norm: 	
	@printf "$(YELLOW)\n🔍 Revisando con norminette...$(RESET)\n"
	@norminette includes
	@norminette $(SRC)
	@norminette utils

# Incluir dependencias automáticas
-include $(DEP)

.PHONY: all clean fclean re norm run