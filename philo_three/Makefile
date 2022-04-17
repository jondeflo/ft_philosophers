NAME = philo_three

SRC_DIR = srcs/
OBJ_DIR = obj/
INC_DIR = includes/

INCLUDES = -I$(INC_DIR)

CC = gcc
FLAGS = -g -Wall -Wextra -Werror
MMD = -MMD

SRC_DIR_P = $(SRC_DIR)parser/
FILES = main.c\
		parce.c\
		utils.c\
		init.c\

OBJ_FILES = $(FILES:.c=.o)

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(INCLUDES) $(OBJ)

-include $(OBJ:.o=.d)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	$(CC) $(MMD) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ_FILES)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all