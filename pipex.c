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
//	for (int i = 0; split_cmd[i] != NULL; i++)
//	{
//		ft_putstr_fd(split_cmd[i], 2);
//		ft_putstr_fd("\n", 2);
//	}
//	ft_putstr_fd("ahhhhhhhhhhh", 2);
//	ft_putstr_fd("\n", 2);
//	ft_putstr_fd(exec_path, 2);
	if (execve(exec_path, split_cmd, env) == -1)
	{
//		ft_putstr_fd("ahhhhhhhhhhh", 2);
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
		input_fd = open_input_or_output_file(argv[1], "input");
		dup2(input_fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
//		ft_putstr_fd("first cmd", 2);
//		ft_putstr_fd("\n", 2);
		exec(argv[2], env);
	}
	else
	{
		close(pipe_fd[1]);
		output_fd = open_input_or_output_file(argv[4], "output");
		dup2(output_fd, STDOUT_FILENO);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
//		ft_putstr_fd("second cmd", 2);
//		ft_putstr_fd("\n", 2);
		exec(argv[3], env);
	}
}



void	execute_parent_process(int *pipe_fd, pid_t *process_id)
{
	int	status_code1;
	int	status_code2;
	int	exit_status;
//	int exit_status2;

	close(pipe_fd[0]);
	close(pipe_fd[1]);

	waitpid(process_id[0], &status_code1, 0);
	waitpid(process_id[1], &status_code2, 0);

//	exit_status = WEXITSTATUS(status_code1);
//
//	if (exit_status != 0)
//	{
//		ft_putstr_fd("first child exit", 2);
//		ft_putnbr_fd(exit_status, 2);
//		exit(exit_status);
//	}

//	exit_status2 = WEXITSTATUS(status_code1);
//	ft_putnbr_fd(exit_status2, 2);

	exit_status = WEXITSTATUS(status_code2);
//	ft_putstr_fd("second child exit", 2);
//	ft_putstr_fd("\n", 2);
//	ft_putnbr_fd(exit_status, 2);
	exit(exit_status);
}

//void	execute_parent_process(int *pipe_fd, pid_t *process_id)
//{
//	int	status_code1;
//	int	status_code2;
//	int	exit_status;
//	int	exit_status2;
//
//	close(pipe_fd[0]);
//	close(pipe_fd[1]);
//
//	waitpid(process_id[0], &status_code1, 0);
//	waitpid(process_id[1], &status_code2, 0);
//
//	exit_status = WEXITSTATUS(status_code1);
//	exit_status2 = WEXITSTATUS(status_code2);
//
//	if (exit_status == 1)
//		exit(exit_status);
//	else if (exit_status2 == 1)
//		exit(exit_status2);
//	else
//		exit(0);
//}

// move this out in a single main and this file should be a executer.c or something
int	main(int argc, char *argv[], char *env[])
{
	int		pipe_fd[2];
	int		file_access_status;
	int		cmd_index;
	pid_t	process_id[2];
//	int		last_status;

	cmd_index = 1;
	if (argc != 5)
		return (print_error_msg(ERR_INPUT));
	// check only one file
	file_access_status = has_file_access(argv[1]);
	if (file_access_status == -1)
		print_error_msg_and_exit(ERR_ACCESS_FAIL);
	if (pipe(pipe_fd) == -1)
		print_error_msg_and_exit(ERR_PIPE);
	while (++cmd_index < argc - 1)
	{
		process_id[cmd_index - 2] = fork();
//	printf("PROCESS ID after fork %d\n", process_id[cmd_index - 2]);
		if (process_id[cmd_index - 2] == 0)
			execute_child_process(argv, pipe_fd, env, cmd_index);
//		printf("Child PID0: %d\n", getpid());
		if (process_id[cmd_index - 2] == -1)
			print_error_msg_and_exit(ERR_FORK);
	}

	execute_parent_process(pipe_fd, process_id);
	return (0);
}
