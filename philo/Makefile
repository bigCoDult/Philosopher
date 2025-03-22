NAME = philo

CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g -O0

SRC_DIR = ./src
OBJ_DIR = ./obj
INC = -I.

SRC = $(SRC_DIR)/main.c \
	$(SRC_DIR)/eating.c \
	$(SRC_DIR)/ft_for_atoitoa.c \
	$(SRC_DIR)/ft_utils.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/life.c \
	$(SRC_DIR)/monitor.c \
	$(SRC_DIR)/time.c \
	$(SRC_DIR)/validate.c
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME):  $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
