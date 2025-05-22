# Nombre del ejecutable
NAME := philo

# Compilador y flags
CC = cc
CFLAGS := -Wall -Werror -Wextra -g -MMD -MP -fsanitize=thread

# Rutas de fuentes y objetos
SRC :=	src/eat_routine.c \
		src/free_and_stop.c \
		src/init.c \
		src/logs.c \
		src/main.c \
		src/parser.c \
		src/philo_routine.c \
		src/reaper.c \
		src/usleep.c \
		utils/ft_atoul.c \
		utils/ft_calloc.c \
		utils/ft_free_exit.c \
		utils/ft_is_str_digit.c \
		utils/ft_printf_utils.c \
		utils/ft_printf.c \
		utils/ft_putnbr_fd.c \
		utils/ft_putstr_fd.c \
		utils/ft_strlen.c \
		utils/ft_strncmp.c \
		utils/ft_substr.c \


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

$(NAME): $(OBJ)
	@printf "$(CYAN)\r🔗 Enlazando: $(NAME)                     $(RESET)\n"
	@$(CC) $(OBJ) -o $(NAME) $(CFLAGS)
	@printf "$(GREEN)\n✅ Compilación completa$(RESET)\n"

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(BLUE)\r⚙️  Compilando: $<                         $(RESET)"
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