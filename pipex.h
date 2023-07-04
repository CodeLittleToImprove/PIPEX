/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:12:40 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/05/25 19:12:40 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>


# define INPUT 1
# define OUTPUT 2
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe Error"
# define ERR_CMD "pipex: "
# define ERR_EXEC "Execve Error"
# define ERR_FORK "Fork Error"
# define ERR_OPEN_FILE "pipex: "
# define ERR_ACCESS_FAIL "pipex: "
# define ERR_IMPOSSIBLE "Impossible stop sabotating my Program :("
# define ERR_CHILD_PROCESS "Error with waiting for child process"
# define ERR_CHILD_SIGNAL "Received signal to terminate child process"

// pipex.c
void	exec(char *cmd, char **env);
void	execute_child_process(char *argv[], int *pipe_fd, char *env[], int cnum);
void	execute_parent_process(int *pipe_fd, pid_t *process_id);

// util.c
void	ft_free_array(char **array);
int		open_input_or_output_file(char *filename, int in_or_out);
int		has_file_access(const char *input_filename);
//			const char *output_filename);
char	*get_env_value_by_name(char *envVarName, char **env);
char	*get_exec_path(char *cmd, char **env);
char	**parse_command_with_quotes(char *cmd);

// error.c
int		print_error_msg(char *error);
void	print_error_cmd_not_found_and_exit(char *split_cmd, char *error);
void	print_error_msg_and_exit(char *error);
//void	print_failed_cmd_msg_and_exit(char *split_cmd);
void	print_error_msg_and_exit_positive(char *error);
void	print_error_open_file_and_exit(char *filename, char *error);
#endif