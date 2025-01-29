NAME = pipex
BONUS_NAME = pipex_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibs/libft 
B_CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibs/libft -Ibonus/get_next_line

RM = rm -rf

SOURCE_DIR = ./srcs
BONUS_DIR = ./bonus
GNL_DIR = ./bonus/get_next_line
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
				$(BONUS_DIR)/here_doc.c \
				$(GNL_DIR)/get_next_line.c \
				$(GNL_DIR)/get_next_line_utils.c \
				$(COMMON_SRCS)


LIBFT = $(LIB_DIR)/libft/libft.a

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIB_DIR)/libft
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(MAKE) -C $(LIB_DIR)/libft
	$(CC) $(B_CFLAGS) $(BONUS_SRCS) $(LIBFT) -o $(NAME)

clean:
	$(MAKE) -C $(LIB_DIR)/libft fclean

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)
	$(RM) outfile.txt

re: fclean all

.PHONY: all bonus clean fclean re
