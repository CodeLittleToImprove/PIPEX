/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:44:17 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/07/04 18:07:18 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	int		pipe_fd[2];
	int		file_access_status;
	int		cmd_index;
	pid_t	process_id[2];

	cmd_index = 1;
	if (argc != 5)
		return (print_error_msg(ERR_INPUT));
	file_access_status = has_file_access(argv[1]);
	if (file_access_status == -1)
		//fix this the logic is wrong
		print_error_msg_and_exit(ERR_ACCESS_FAIL);
	if (pipe(pipe_fd) == -1)
		print_error_msg_and_exit(ERR_PIPE);
	while (++cmd_index < argc - 1)
	{
		process_id[cmd_index - 2] = fork();
		if (process_id[cmd_index - 2] == 0)
			execute_child_process(argv, pipe_fd, env, cmd_index);
		if (process_id[cmd_index - 2] == -1)
			print_error_msg_and_exit(ERR_FORK);
	}
	execute_parent_process(pipe_fd, process_id);
	return (0);
}
