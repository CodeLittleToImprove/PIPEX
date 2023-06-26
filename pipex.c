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
// check waitpid and weexit command to replace my exit stuff
// maybe change open output first and then input
void	exec(char *cmd, char **env)
{
	char	**split_cmd;
	char	*exec_path;

	split_cmd = ft_split(cmd, ' ');
	exec_path = get_exec_path(split_cmd[0], env);
	if (execve(exec_path, split_cmd, env) == -1)
	{
		free(exec_path);
		ft_free_array(split_cmd);
		print_error_msg_and_exit(ERR_EXEC);
	}
}

void	execute_child_process(char *argv[], int *pipe_fd, char *env[])
{
	int	input_fd;

	input_fd = open_input_or_output_file(argv[1], "input");
	dup2(input_fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	exec(argv[2], env);
}

void	execute_parent_process(char *argv[], int *pipe_fd, char *env[])
{
	int	output_fd;

	output_fd = open_input_or_output_file(argv[4], "output");
	dup2(output_fd, STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	exec(argv[3], env);
}

// move this out in a single main and this file should be a executer.c or something
int	main(int argc, char *argv[], char *env[])
{
	int		pipe_fd[2];
	int		file_access_status;
	int		cmd_index;
	pid_t	process_id[2];
//	int		status;

	cmd_index = 2;
	if (argc != 5)
		return (print_error_msg(ERR_INPUT));
	file_access_status = has_file_access(argv[1], argv[4]);
	if (file_access_status == -1)
		print_error_msg_and_exit(ERR_ACCESS_FAIL);
	if (pipe(pipe_fd) == -1)
		print_error_msg_and_exit(ERR_PIPE);
	while (cmd_index < argc - 2)
	{
		process_id[cmd_index - 2] = fork();
//	printf("PROCESS ID after fork %d\n", process_id);
		if (process_id[cmd_index - 2] == 0)
			execute_child_process(argv, pipe_fd, env);
//		printf("Child PID0: %d\n", getpid());
		if (process_id[cmd_index - 2] == -1)
			print_error_msg_and_exit(ERR_FORK);
	}
// start to work to refactor the child procesess

//	printf("Parent PID: %d\n", getpid());
//	printf("PROCESS ID %d\n", process_id);
//	waitpid(process_id, &status, 0);
	execute_parent_process(argv, pipe_fd, env);
	return (0);
}
