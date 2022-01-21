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
		srcs/program_execution/cmd_list.c \
		srcs/program_execution/cmd_list_wrapper.c \
		\
		srcs/parsing/cmd_layout/generate_operators_layout.c \
		srcs/parsing/cmd_layout/get_next_operator.c \
		srcs/parsing/cmd_layout/get_operator_strlen.c \
		\
		srcs/parsing/quotes/parse_quotes.c \
		\
		srcs/parsing/redirections/parse_redirections.c \
		srcs/parsing/redirections/open_file.c \
		\
		srcs/parsing/wildcards/interpret_wildcards.c \
		srcs/parsing/wildcards/retrieve_files.c \
		\
		srcs/exit/clean_exit.c \
		srcs/exit/check_exit.c \
		\
		srcs/parsing/get_one_arg.c \
		srcs/parsing/interpret_arguments.c \
		srcs/parsing/is_valid_bash_var.c \
		srcs/parsing/parse_one_program.c \
		srcs/parsing/parse_whole_line.c \
		srcs/parsing/utils.c \
		srcs/parsing/utils_2.c \
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

CC = gcc -g -fsanitize=address #-Wall -Wextra -Werror

%.o: %.c
	@$(CC) -c $< -o $@
	@echo "\033[0;96mCompiling \033[1;96m$<\033[0m"

$(NAME):	$(LIBFT) $(OBJS)
	@echo "\033[0;95mLinking \033[0;95m($(OBJS)) into \033[1;35m$(NAME)\033[0m"
	@$(CC) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "\033[1;92mDONE"
#	@./test.sh

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
