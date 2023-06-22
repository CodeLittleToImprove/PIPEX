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
# define ERR_CMD "Command not found\n"
# define ERR_EXEC "Execve Error"
# define ERR_FORK "Fork Error"
# define ERR_OPEN_FAIL  "Open file Error"
# define ERR_IMPOSSIBLE "Impossible stop sabotating my Program :("
# define INPUTFILE 0
# define OUTPUTFILE 1

// util.c
void	ft_free_array(char **array);
int		open_input_or_output_file(char *filename, int in_or_out);
char	*get_env_value_by_name(char *envVarName, char **env);
char	*get_exec_path(char *cmd, char **env);

// error.c
int		print_error_msg(char *error);
void	print_error_cmd_not_found_and_exit(char *split_cmd);
void	print_error_msg_and_exit(char *error);
void	print_failed_cmd_msg_and_exit(char *split_cmd);
#endif