SRCS =	minishell.c \
		search_executable.c \
		execute_command.c \
		cmd_list.c \
		parse/parsing.c \
			./builtins/environment/add_variable.c \
			./builtins/environment/get_variable.c \
			./builtins/environment/remove_variable.c \
			./builtins/environment/var_list.c \
			./builtins/environment/get_env.c \
			./builtins/environment/env.c \
			./builtins/environment/export.c \
			./builtins/environment/unset.c \
			./builtins/cd.c \
			./builtins/pwd.c \


LIBFT = ./libft/libft.a

OBJS = $(SRCS:.c=.o)

NAME = minishell

CC = gcc #-Wall -Wextra -Werror

%.o: %.c
	@$(CC) -c $< -o $@
	@echo "\033[0;96mCompiling \033[1;96m$<\033[0m"

$(NAME):	$(LIBFT) $(OBJS) echo
	@echo "\033[0;95mLinking \033[0;95m($(OBJS)) into \033[1;35m$(NAME)\033[0m"
	@$(CC) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "\033[1;92mDONE"

echo:
	$(CC) ./builtins/echo.c $(LIBFT) -o ./execs/echo

$(LIBFT):
	$(MAKE) -j -C libft

all:		$(NAME)

clean:
	@rm -f $(OBJS)
	@echo "\033[0;91mRemoving \033[0;31m$(OBJS)\033[0m"
	@make -C libft clean
	@rm -f echo

fclean:		clean
	@rm -f $(NAME)
	@echo "\033[0;91mRemoving \033[0;31m$(NAME)\033[0m"
	@make -C libft fclean

re:			fclean all

.PHONY:	all clean fclean re
