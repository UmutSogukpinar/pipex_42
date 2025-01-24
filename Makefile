NAME = pipex
BONUS_NAME = pipex_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibs/libft -Ilibs/my_printf

RM = rm -rf

BONUS_DIR = ./bonus
SOURCE_DIR = ./srcs
LIB_DIR = ./libs

COMMON_SRCS =	$(SOURCE_DIR)/init.c \
                $(SOURCE_DIR)/shut.c \
                $(SOURCE_DIR)/execution.c

SRCS =	$(SOURCE_DIR)/main.c \
		$(SOURCE_DIR)/process.c \
		$(COMMON_SRCS)

BONUS_SRCS =	$(BONUS_DIR)/main_bonus.c \
				$(BONUS_DIR)/process_bonus.c \
				$(BONUS_DIR)/utils_bonus.c \
				$(BONUS_DIR)/init_bonus.c \
				$(COMMON_SRCS)


LIBFT = $(LIB_DIR)/libft/libft.a
PRINTF = $(LIB_DIR)/printf/libftprintf.a

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIB_DIR)/libft
	$(MAKE) -C $(LIB_DIR)/printf
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(PRINTF) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(MAKE) -C $(LIB_DIR)/libft
	$(MAKE) -C $(LIB_DIR)/printf
	$(CC) $(CFLAGS) $(BONUS_SRCS) $(LIBFT) $(PRINTF) -o $(NAME)

clean:
	$(MAKE) -C $(LIB_DIR)/libft fclean
	$(MAKE) -C $(LIB_DIR)/printf fclean

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)
	$(RM) outfile.txt

re: fclean all

.PHONY: all bonus clean fclean re
