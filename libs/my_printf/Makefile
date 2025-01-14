NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
FILES = ft_printf.c \
		ft_printf_utils.c \
		ft_printf_utils2.c

OBJS = $(FILES:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re