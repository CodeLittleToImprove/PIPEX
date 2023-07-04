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

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe Error"
# define ERR_CMD "pipex: "
# define ERR_EXEC "Execve Error"
# define ERR_FORK "Fork Error"
# define ERR_OPEN_FAIL "pipex: "
# define ERR_ACCESS_FAIL "Access file Error"
# define ERR_IMPOSSIBLE "Impossible stop sabotating my Program :("
# define ERR_CHILD_PROCESS "Error with waiting for child process"
# define ERR_CHILD_SIGNAL "Received signal to terminate child process"

// util.c
void	ft_free_array(char **array);
int		open_input_or_output_file(char *filename, char *in_or_out);
int		has_file_access(const char *input_filename);
//			const char *output_filename);
char	*get_env_value_by_name(char *envVarName, char **env);
char	*get_exec_path(char *cmd, char **env);
char	**parse_command_with_quotes(char *cmd);

// error.c
int		print_error_msg(char *error);
void	print_error_cmd_not_found_and_exit(char *split_cmd);
void	print_error_msg_and_exit(char *error);
//void	print_failed_cmd_msg_and_exit(char *split_cmd);
void	print_error_msg_and_exit_positive(char *error);
void	print_error_open_file_and_exit(char *filename, char *error);
#endif