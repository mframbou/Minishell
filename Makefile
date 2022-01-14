#                 .-.                       .                         
#                / -'                      /                          
# .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (              
#  )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .   
# '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /    
#            -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.  
#                           `-' \/ (   )/    (   )  )/   )(   / (  |  
#                               /\  `-'/      `-'  '/   (  `-'-..`-'-'
#                           `._;  `._;                   `-           


SRCS =	srcs/minishell.c \
		\
		srcs/program_execution/search_executable.c \
		srcs/program_execution/execute_command.c \
		\
		srcs/parsing/cmd_list_wrapper.c \
		srcs/parsing/cmd_list.c \
		srcs/parsing/get_one_arg.c \
		srcs/parsing/interpret_arguments.c \
		srcs/parsing/is_valid_bash_var.c \
		srcs/parsing/parse_one_program.c \
		srcs/parsing/parse_whole_line.c \
		srcs/parsing/utils.c \
		\
		builtins/environment/add_variable.c \
		builtins/environment/get_variable.c \
		builtins/environment/remove_variable.c \
		builtins/environment/var_list.c \
		builtins/environment/get_env.c \
		builtins/environment/env.c \
		builtins/environment/export.c \
		builtins/environment/unset.c \
		builtins/cd.c \
		builtins/pwd.c \
		builtins/exit.c \
		builtins/echo.c \

LIBFT = ./libft/libft.a

OBJS = $(SRCS:.c=.o)

NAME = minishell

CC = gcc #-g -fsanitize=address #-Wall -Wextra -Werror

%.o: %.c
	@$(CC) -c $< -o $@
	@echo "\033[0;96mCompiling \033[1;96m$<\033[0m"

$(NAME):	$(LIBFT) $(OBJS)
	@echo "\033[0;95mLinking \033[0;95m($(OBJS)) into \033[1;35m$(NAME)\033[0m"
	@$(CC) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "\033[1;92mDONE"
	@say -v Amelie pouette

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
