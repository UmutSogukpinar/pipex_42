NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f
FILES =	ft_atoi.c \
		ft_memchr.c \
		ft_split.c \
		ft_strncmp.c \
		ft_bzero.c \
		ft_memcmp.c \
		ft_strchr.c \
		ft_strnstr.c \
		ft_calloc.c \
		ft_memcpy.c \
		ft_strdup.c \
		ft_strrchr.c \
		ft_isalnum.c \
		ft_memmove.c \
		ft_striteri.c \
		ft_strtrim.c \
		ft_isalpha.c \
		ft_memset.c \
		ft_strjoin.c \
		ft_substr.c \
		ft_isascii.c \
		ft_putchar_fd.c \
		ft_strlcat.c \
		ft_tolower.c \
		ft_isdigit.c \
		ft_putendl_fd.c \
		ft_strlcpy.c \
		ft_toupper.c \
		ft_isprint.c \
		ft_putnbr_fd.c \
		ft_strlen.c \
		ft_itoa.c \
		ft_putstr_fd.c \
		ft_strmapi.c

BONUS = ft_lstadd_front.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstlast.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lstsize.c \
		ft_lstclear.c \
		ft_lstadd_back.c

OBJECTS = $(FILES:.c=.o)
BONUS_OBJ = $(BONUS:.c=.o)

all: ${NAME}

$(NAME): $(OBJECTS)
	$(AR) $(NAME) $(OBJECTS)

bonus: $(OBJECTS) $(BONUS_OBJ)

	$(AR) $(NAME) $(OBJECTS) $(BONUS_OBJ)

clean:
	${RM} ${OBJECTS} ${BONUS_OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re