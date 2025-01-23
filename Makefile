NAME = pipex
BONUS_NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibs/libft -Ilibs/my_printf

RM = rm -rf

BONUS_DIR = ./bonus
SOURCE_DIR = ./srcs
LIB_DIR = ./libs


SRCS =	$(SOURCE_DIR)/main.c \
		$(SOURCE_DIR)/init.c \
		$(SOURCE_DIR)/shut.c \
		$(SOURCE_DIR)/execution.c \
		$(SOURCE_DIR)/process.c \

BONUS_SRCS =	$(SOURCE_DIR)/init.c \
				$(SOURCE_DIR)/shut.c \
				$(SOURCE_DIR)/execution.c \
				$(BONUS_DIR)/main_bonus.c \

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(SRCS)
	$(MAKE) -C $(LIB_DIR)/libft
	$(MAKE) -C $(LIB_DIR)/printf
	$(CC) $(CFLAGS) $(SRCS) $(LIB_DIR)/libft/libft.a $(LIB_DIR)/printf/libftprintf.a -o $(NAME)

$(BONUS_NAME): $(BONUS_SRCS)
	$(MAKE) -C $(LIB_DIR)/libft
	$(MAKE) -C $(LIB_DIR)/printf
	$(CC) $(CFLAGS) $(BONUS_SRCS) $(LIB_DIR)/libft/libft.a $(LIB_DIR)/printf/libftprintf.a -o $(NAME)

clean: 
	$(MAKE) -C $(LIB_DIR)/libft fclean
	$(MAKE) -C $(LIB_DIR)/printf fclean

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re
