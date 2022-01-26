# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dsalaman <dsalaman@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/01/26 08:09:08 by dsalaman      #+#    #+#                  #
#    Updated: 2022/01/26 08:09:14 by dsalaman      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := philo
OBJ_DIR := obj/
SRC_DIR := src/
INC_DIR := includes/
CFLAGS := -Wall -Wextra -Werror
SRC := main.c utils.c setup_args.c cleaning.c actions.c time_functions.c \
		simulation.c
SRC_PATH:= $(addprefix $(SRC_DIR), $(SRC))
OBJS := $(SRC_PATH:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $^ -o $@
	@echo "\033[38;5;10mphilo executable successfully created.\n\033[0m"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(INC_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Objects were removed - clean."

fclean: clean
	@rm -f $(NAME)
	@echo "\033[38;5;81mphilo executable was removed - fclean.\033[0m"

norm:
	norminette $(SRC_DIR) $(INC_DIR)

re: fclean all

.PHONY: all clean fclean re