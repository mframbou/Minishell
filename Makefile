#                 .-.                       .                         
#                / -'                      /                          
# .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (              
#  )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .   
# '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /    
#            -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.  
#                           `-' \/ (   )/    (   )  )/   )(   / (  |  
#                               /\  `-'/      `-'  '/   (  `-'-..`-'-'
#                           `._;  `._;                   `-           

#CPUS ?= $(shell sysctl -n hw.ncpu || echo 1)
#MAKEFLAGS += --jobs=$(CPUS)	# I'm fast as fuck boi, not working on make re

SRCS =	srcs/minishell.c \
		srcs/signals.c \
		\
		srcs/libft/ft_malloc/ft_free.c \
		srcs/libft/ft_malloc/ft_malloc.c \
		\
		srcs/parsing/exit_status/exit_status.c \
		\
		srcs/parsing/check_syntax.c \
		\
		srcs/program_execution/search_executable.c \
		srcs/program_execution/execute_command.c \
		srcs/program_execution/execute_one_command.c \
		srcs/program_execution/parse_and_execute_line.c \
		srcs/program_execution/cmd_list.c \
		srcs/program_execution/cmd_list_wrapper.c \
		srcs/program_execution/execute_builtin.c \
		srcs/program_execution/utils.c \
		\
		srcs/parsing/cmd_layout/generate_operators_layout.c \
		srcs/parsing/cmd_layout/generate_operators_layout2.c \
		srcs/parsing/cmd_layout/get_next_operator.c \
		srcs/parsing/cmd_layout/get_operator_strlen.c \
		srcs/parsing/cmd_layout/utils.c \
		\
		srcs/parsing/quotes/parse_quotes.c \
		srcs/parsing/quotes/utils.c \
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
		srcs/parsing/parse_one_program.c \
		srcs/parsing/parse_whole_line.c \
		srcs/parsing/utils.c \
		srcs/parsing/utils_2.c \
		\
		srcs/parsing/parentheses/utils_parentheses.c \
		\
		srcs/builtins/environment/add_variable.c \
		srcs/builtins/environment/get_variable.c \
		srcs/builtins/environment/remove_variable.c \
		srcs/builtins/environment/var_list.c \
		srcs/builtins/environment/get_env.c \
		srcs/builtins/environment/env.c \
		srcs/builtins/environment/export.c \
		srcs/builtins/environment/unset.c \
		srcs/builtins/cd.c \
		srcs/builtins/pwd.c \
		srcs/builtins/exit.c \
		srcs/builtins/echo.c \

LIBFT = ./srcs/libft/libft.a

READLINE = ./srcs/libreadline.a -ltermcap # Need to include termcap to use readline

OBJS = $(SRCS:.c=.o)

NAME = minishell

CC = gcc -Wall -Wextra -Werror #-g -fsanitize=address

AQUA = \033[0;96m
AQUA_BOLD = \033[1;96m

%.o: %.c
	@$(CC) -c $< -o $@
	@echo "$(AQUA)Compiling $(AQUA_BOLD)$<\033[0m"

$(NAME):	$(LIBFT) $(OBJS)
	@echo "\033[0;95mLinking \033[0;95m($(OBJS)) into \033[1;35m$(NAME)\033[0m"
	@$(CC) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)
	@echo "\033[1;92mDONE"
	@./test.sh

$(LIBFT):
	$(MAKE) -j -C ./srcs/libft

all:		$(NAME)

clean:
	@rm -f $(OBJS)
	@echo "\033[0;91mRemoving \033[0;31m$(OBJS)\033[0m"
	@make -C ./srcs/libft clean
	@rm -f echo

fclean:		clean
	@rm -f $(NAME)
	@echo "\033[0;91mRemoving \033[0;31m$(NAME)\033[0m"
	@make -C ./srcs/libft fclean

re:			fclean all

.PHONY:	all clean fclean re
