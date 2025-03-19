# Important
NAME = philosopher
CC = cc
RM = rm -rf

# 나중에는 디버깅 옵션 빼야함
CFLAGS = -Wall -Wextra -Werror -g -O0
# CFLAGS = -Wall -Wextra -Werror

# Directory
SRC_DIR = ./src
OBJ_DIR = ./obj
INC = -I.

# src/obj file
# SRC = \
# 	$(addprefix $(SRC_DIR)/, \
# 	main.c \
# 	ft_utils.c \
# 	validate.c \
# 	time.c \
# )
SRC = $(wildcard $(SRC_DIR)/*.c)
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
