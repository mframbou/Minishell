/* ************************************************************************** */
/*                       .-.                       .                          */
/*                      / -'                      /                           */
/*       .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (               */
/*        )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )         .    */
/*   By: '/   /   (`.'  /      `-'-.-/   /.- (.''--'`-`-'  `--':        /     */
/*                  -'            (   \  / .-._.).--..-._..  .-.  .-../ .-.   */
/*   Created: 22-01-2022  by       `-' \/ (   )/    (   )  )/   )(   / (  |   */
/*   Updated: 24-01-2022 01:37 by      /\  `-'/      `-'  '/   (  `-'-..`-'-' */
/*                                 `._;  `._;                   `-            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Takes current fd and return either a new fd (if redirection)
	or the same if there is no redirection (input so < and <<)

	If an input redirection is found, close the previous fd if != -1
*/
int	get_fd_for_input_redirection_if_any(int current_fd, t_redirection *redir)
{
	int	fd;

	fd = current_fd;
	if (redir->in_filename)
	{
		if (redir->in_redir_type == SINGLE_LEFT_REDIRECT)
		{
			close(current_fd);
			fd = open_file_for_redirection(redir->in_filename, \
											redir->in_redir_type);
			if (fd == -1)
				return (-2);
		}
		else if (redir->in_redir_type == DOUBLE_LEFT_REDIRECT)
		{
			close(current_fd);
			fd = read_until_delimiter(redir->in_filename);
		}
	}
	return (fd);
}
/*
	Returns next read fd, or -2 on error
*/
int	execute_program_if_found(char **args, int read_fd, int *waitpid_count)
{
	int		new_read_fd;
	char	*program;

	if (is_builtin(args[0]))
		new_read_fd = execute_builtin(args);
	else
	{
		if (has_slash(args[0]))
			program = search_absolute_path_program(args[0]);
		else
			program = is_program_in_path(args[0]);
		if (program)
		{
			(*waitpid_count)++;
			new_read_fd = execute_program(read_fd, program, args);
			if (new_read_fd == -2)
			{
				perror("An error occured while executing pipeline: \n");
				// TODO proper exit
				return (-2);
			}
		}
		else
		{
			perror(program); // If one command is not found or no perm etc., break the whole pipeline
			//clear_cmd_list();
			close(read_fd);
			//flush_pipe(read_fd); // Do not print to output since it failed, eg echo test | pouet should not output "test'\n pouet command not found" but just "pouet command not found"
			return (-2);
		}
		//free(program);
	}
	return (new_read_fd);
}


int execute_cmd_lst(int read_fd, t_cmd *cmd_lst);
int	has_syntax_error(char *line);
int	are_parentheses_invalid(char *line);


/*
	Executes the commands in the line, sends info to stdin from 'read_fd' if != -1
	Returns the read_fd of the last command of the line

	First call will be with input_read_fd = -1, but then it will
	be recursively called
*/
int	parse_and_execute_line(int input_read_fd, char *line)
{
	t_cmd	*cmd_list;
	int		output_read_fd;

	if (are_parentheses_invalid(line))
		return -2 ;
	if (has_syntax_error(line))
	{
		printf("Syntax error near index %d in '%s' ('%c')\n", has_syntax_error(line) - 1, line,  line[has_syntax_error(line) - 1]);
		return -2 ;
	}
	cmd_list = parse_cmds(line);
	if (cmd_list)
		output_read_fd = execute_cmd_lst(input_read_fd, cmd_list);
	//input_read_fd = output_read_fd;
	//clear_cmd_list(&cmd_list);
	return (output_read_fd);
	//clear_cmd_list();
}


/*
	read_fd = fd to read from for next command
	new_read_fd = fd the first command has written to

	"sleep 4 | echo test && echo salut" will execute normaly sleep and echo test
		then wait for them and when they are all finished execute the && or the ||
	so need to wait for all childrens before doing && or ||
*/
int execute_cmd_lst(int read_fd, t_cmd *cmd_lst)
{
	t_cmd	*curr;
	//int		read_fd;
	int		new_read_fd;
	char	*program;
	char	buf;
	int		exit_status;
	int		waitpid_count = 0;
	int		cmd_count = 0;

	curr = cmd_lst;
	new_read_fd = -1;
	//printf("|=%d ||=%d &&=%d\n", PIPE_CHAR, OR_CHAR, AND_CHAR);
	while (curr)
	{
		//printf("Current command: %s, redir type: %d\n", curr->args[0], curr->next_cmd_operator);
		cmd_count++;
		if (curr->parentheses_content) // Execute it before
		{
			new_read_fd = parse_and_execute_line(read_fd, curr->parentheses_content);
			//if (read_fd >= 0) Do not close here, execute_cmd_list will do it
			//	close(read_fd);
			if (new_read_fd == -2)
			{
				free_redirections(cmd_lst);
				//clear_cmd_list(&cmd_lst);
				
				return (-2);
			}
			read_fd = new_read_fd;
			curr = curr->next;
			continue ;
		}
		read_fd = get_fd_for_input_redirection_if_any(read_fd, &curr->redirection);
		if (read_fd == -2)
		{
			perror("An error occured while opening file:");
			read_fd = -1;
		}
		new_read_fd = execute_program_if_found(curr->args, read_fd, &waitpid_count);
		if (read_fd >= 0)
			close(read_fd);
		if (new_read_fd == -2)
		{
			free_redirections(cmd_lst);
			//clear_cmd_list(&cmd_lst);
			
			return (-2);
		}
		read_fd = new_read_fd;
		if (curr->redirection.out_filename != NULL)
		{
			int fd = open_file_for_redirection(curr->redirection.out_filename, curr->redirection.out_redir_type);
			if (fd == -1)
			{
				perror("Error while opening file for writing");
				return (-2);
			}
			while (read(new_read_fd, &buf, 1) > 0)
				write(fd, &buf, 1);
			close(fd);
			new_read_fd = -1;
			read_fd = -1;
		}

		if (curr->next_cmd_operator == AND_CHAR || curr->next_cmd_operator == OR_CHAR)
		{
			
			if (waitpid(g_pid, &exit_status, 0) != -1) // wait for the last process, then wait for all other
				set_exit_status(exit_status);
			while (wait(NULL) > 0);	// Wait for all other childs but don't save exit status
			flush_pipe(read_fd); // flush pipe since it's redirected to stdout and not a pipe
			read_fd = -1;
			new_read_fd = -1;
			// Then check
			if (curr->next_cmd_operator == AND_CHAR && *get_exit_status() != 0) // Skip the next command
			{
				curr = curr->next; // go to next cmd as usual
				if (curr)
					curr = curr->next; // then one after
				continue ;
			}
			else if (curr->next_cmd_operator == OR_CHAR && *get_exit_status() == 0)
			{
				curr = curr->next; // go to next cmd as usual
				if (curr)
					curr = curr->next; // then one after
				continue ;
			}
		}
		
		curr = curr->next;

		if (should_exit() && cmd_count == 1 && !curr) // Only exit if it's the only command
		{
			//clear_cmd_list(&cmd_lst);
			flush_pipe(read_fd);
			free_redirections(cmd_lst);
			rl_clear_history();
			free_environment();
			//ft_free_all();
			exit(*get_exit_status());
		}
		else if (should_exit())
		{
			set_should_exit(0); // if its not the only one, discard
		}
	}
	return (read_fd);
}
