NAME    = libgnl.a

CC      = cc
AR      = ar rcs
RM      = rm -f

CFLAGS  = -Wall -Wextra -Werror

SRC     = get_next_line.c \
          get_next_line_utils.c

OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
