#
# Created by dsalaman on 08/07/2021.
#

NAME 		= philo
OBJ_DIR 	= obj/
SRC_DIR 	= src/
INC_DIR 	= includes/
FLAGS 		= -Wall -Wextra -Werror -I$(INC_DIR) -pthread
SRC 		= main.c utils.c setup_args.c clean.c actions.c
SRC_PATH	= $(addprefix $(SRC_DIR), $(SRC))
OBJS 		= $(SRC_PATH:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "\033[38;5;10mphilo successfully created.\n\033[0m"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Objects were removed - clean."

fclean: clean
	@rm -f $(NAME)
	@echo "\033[38;5;81mphilo executable was removed - fclean.\033[38;5;81m"

re: fclean all
.PHONY: all clean fclean re