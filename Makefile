SRCS =	minishell.c \
			./builtins/cd.c \
			./builtins/echo.c \
			./builtins/pwd.c \
				./builtins/environment/add_variable.c \
				./builtins/environment/env.c \
				./builtins/environment/export.c \
				./builtins/environment/get_variable.c \
				./builtins/environment/remove_variable.c \
				./builtins/environment/unset.c \
				./builtins/environment/var_list.c \

LIBFT = ./libft/libft.a

OBJS = $(SRCS:.c=.o)

NAME = minishell

CC = gcc #-Wall -Wextra -Werror

%.o: %.c
	@$(CC) -c $< -o $@
	@echo "\033[0;96mCompiling \033[1;96m$<"

$(NAME):	$(LIBFT) $(OBJS)
	@echo "\033[0;95mLinking \033[0;95m($(OBJS)) into \033[1;35m$(NAME)"
	@$(CC) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "\033[1;92mDONE"

$(LIBFT):
	$(MAKE) -j -C libft

all:		$(NAME)

clean:
	@rm -f $(OBJS)
	@echo "\033[0;91mRemoving \033[0;31m$(OBJS)"
	@make -C libft clean

fclean:		clean
	@rm -f $(NAME)
	@echo "\033[0;91mRemoving \033[0;31m$(NAME)"
	@make -C libft fclean

re:			fclean all

.PHONY:	all clean fclean re
