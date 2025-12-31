NAME    = pipex

CC      = cc
RM      = rm -rf

LIB_DIR = libs
SRC_DIR = srcs

LIBFT   = $(LIB_DIR)/libft/libft.a
LIBGNL  = $(LIB_DIR)/gnl/libgnl.a

IS_BONUS ?= 0

CFLAGS  = -Wall -Wextra -Werror \
		  -Iincludes \
		  -I$(LIB_DIR)/libft \
		  -I$(LIB_DIR)/gnl \
		  -DIS_BONUS=$(IS_BONUS)

SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/free.c \
	$(SRC_DIR)/child.c \
	$(SRC_DIR)/execute.c \
	$(SRC_DIR)/utils.c

all: $(NAME)

bonus: fclean
	$(MAKE) IS_BONUS=1 all

$(NAME): $(LIBFT) $(LIBGNL)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(LIBGNL) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)/libft

$(LIBGNL):
	$(MAKE) -C $(LIB_DIR)/gnl

clean:
	$(MAKE) -C $(LIB_DIR)/libft clean
	$(MAKE) -C $(LIB_DIR)/gnl clean

fclean: clean
	$(MAKE) -C $(LIB_DIR)/libft fclean
	$(MAKE) -C $(LIB_DIR)/gnl fclean
	$(RM) $(NAME) outfile.txt

re: fclean all

.PHONY: all bonus clean fclean re
