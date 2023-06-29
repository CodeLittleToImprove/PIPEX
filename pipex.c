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
// when first command returns nothing i get undefined error 0
#include "pipex.h"

//void	exec(char *cmd, char **env)
//{
//	char	**split_cmd;
//	char	*exec_path;
//
//	split_cmd = ft_split(cmd, ' ');
////	ft_putstr_fd(cmd, 2);
////	ft_putstr_fd("done", 2);
////	ft_putstr_fd("\n", 2);
////	for (int i = 0; split_cmd[i] != NULL; i++)
////	{
////		ft_putstr_fd(split_cmd[i], 2);
////		ft_putstr_fd("\n", 2);
////	}
//	exec_path = get_exec_path(split_cmd[0], env);
//	if (execve(exec_path, split_cmd, env) == -1)
//	{
//		free(exec_path);
//		ft_free_array(split_cmd);
//		print_error_msg_and_exit(ERR_EXEC);
//	}
//}

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
	if (execve(exec_path, split_cmd, env) == -1)
	{
//		ft_putstr_fd("error\n", 2);
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

	close(pipe_fd[0]);
	close(pipe_fd[1]);

//	ft_putnbr_fd(process_id[0],2);
//	ft_putstr_fd("\n", 2);
//	ft_putnbr_fd(process_id[1],2);
//	ft_putstr_fd("\n", 2);
	waitpid(process_id[0], &status_code1, 0);
	waitpid(process_id[1], &status_code2, 0);

	if ((status_code1 >> 8) && !(status_code2 >> 8))
	{
		exit(status_code1 >> 8);
	}
	else
	{
		exit(status_code2 >> 8);
	}
//	// why is this not equal?
//	if ((status_code1 != 0) && (status_code2 == 0))
//	{
//		exit(status_code1);
//	}
//	else
//	{
//		exit(status_code2);
//	}

}

//void	execute_parent_process(int *pipe_fd, int num_children)
//{
//	int status;
//	pid_t child_pid;
//	int child_exists = num_children; // Track the number of remaining child processes
//
//	close(pipe_fd[0]);
//	close(pipe_fd[1]);
//
//	while (child_exists > 0)
//	{
//		child_pid = wait(&status);
//		ft_putnbr_fd(child_pid, 2);
//		ft_putstr_fd("\n", 2);
//		if (child_pid > 0)
//		{
//			if (WIFEXITED(status))
//			{
//				if (WEXITSTATUS(status) != 0)
//				{
//					// Handle child process error
//					ft_putnbr_fd(status, 2);
//					ft_putstr_fd("\n", 2);
//					print_error_msg_and_exit(ERR_CHILD_PROCESS);
//				}
//			}
//			else if (WIFSIGNALED(status))
//			{
//				// Handle child process termination due to a signal
//				print_error_msg_and_exit(ERR_CHILD_SIGNAL);
//			}
//
//			child_exists--;
//		}
//	}
//}

// move this out in a single main and this file should be a executer.c or something
int	main(int argc, char *argv[], char *env[])
{
	int		pipe_fd[2];
	int		file_access_status;
	int		cmd_index;
	pid_t	process_id[2];
//	int		status;

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
