/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:59:03 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/05/22 16:48:25 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env)
{
	char	**split_cmd;
	char	*exec_path;

	exec_path = get_exec_path(cmd, env);
	split_cmd = parse_command_with_quotes(cmd);
	if (execve(exec_path, split_cmd, env) == -1)
	{
		free(exec_path);
		ft_free_array(split_cmd);
		print_error_msg_and_exit(ERR_EXEC);
	}
}

void	execute_child_process(char *argv[], int *pipe_fd, char *env[], int cnum)
{
	int	input_fd;
	int	output_fd;

	if (cnum == 2)
	{
		close(pipe_fd[0]);
		input_fd = open_input_or_output_file(argv[1], INPUT);
		dup2(input_fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exec(argv[2], env);
	}
	else
	{
		close(pipe_fd[1]);
		output_fd = open_input_or_output_file(argv[4], OUTPUT);
		dup2(output_fd, STDOUT_FILENO);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		exec(argv[3], env);
	}
}

void	execute_parent_process(int *pipe_fd, pid_t *process_id)
{
	int	status_code1;
	int	status_code2;
	int	exit_status;

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(process_id[0], &status_code1, 0);
	waitpid(process_id[1], &status_code2, 0);
	exit_status = WEXITSTATUS(status_code2);
	exit(exit_status);
}
