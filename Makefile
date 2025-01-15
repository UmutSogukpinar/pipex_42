NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes

RM = rm -rf

SOURCE_DIR = ./srcs
LIB_DIR = ./libs


SRCS = $(SOURCE_DIR)/main.c \

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(SRCS)
	$(MAKE) -C $(LIB_DIR)/libft
	$(CC) $(CFLAGS) $(SRCS) $(LIB_DIR)/libft/libft.a -o $(NAME)

clean: 
	${MAKE} -C ${LIB_DIR}/libft fclean
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

run: ${NAME}
	./${NAME} $(ARGS)