SRCS = ft_malloc/ft_malloc.c ft_malloc/ft_free.c \
ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strlcpy.c \
ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_atoi.c ft_calloc.c\
ft_strncmp.c ft_tolower.c ft_toupper.c ft_striteri.c ft_strcmp.c\
ft_strmapi.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_isspace.c \
free_ft_split.c ft_split_single.c

OBJS = $(SRCS:.c=.o)

NAME = libft.a

HEADERS = libft.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	@$(CC) -c $< -o $@

$(NAME):	$(OBJS)
	@ar rc $(NAME) $(OBJS)
	@echo "\033[1;92mDone compiling libft\033[0m"

all:		$(NAME)

clean:
	@rm -f $(OBJS)
	@echo "\033[0;91mRemoving \033[0;31m$(OBJS)\033[0m"

fclean:		clean
	@rm -f $(NAME)
	@echo "\033[0;91mRemoving \033[0;31m$(NAME)\033[0m"

re:			fclean all

.PHONY:	all clean fclean re bonus
