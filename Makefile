NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibs/libft -Ilibs/my_printf

RM = rm -rf

SOURCE_DIR = ./srcs
LIB_DIR = ./libs


SRCS =	$(SOURCE_DIR)/main.c \
		$(SOURCE_DIR)/init.c \
		$(SOURCE_DIR)/shut.c \
		$(SOURCE_DIR)/execution.c \
		$(SOURCE_DIR)/process.c \

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(SRCS)
	$(MAKE) -C $(LIB_DIR)/libft
	$(MAKE) -C $(LIB_DIR)/printf
	$(CC) $(CFLAGS) $(SRCS) $(LIB_DIR)/libft/libft.a $(LIB_DIR)/printf/libftprintf.a -o $(NAME)

clean: 
	$(MAKE) -C $(LIB_DIR)/libft fclean
	$(MAKE) -C $(LIB_DIR)/printf fclean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME) $(ARGS)

