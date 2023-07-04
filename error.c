/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:06:42 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/06/12 19:06:42 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	print_error_msg(char *error)
{
	write(STDERR_FILENO, error, ft_strlen(error));
	return (1);
}

void	print_error_cmd_not_found_and_exit(char *split_cmd)
{
	write(STDERR_FILENO, "command not found: ", 20);
	write(STDERR_FILENO, split_cmd, ft_strlen(split_cmd));
	write(STDERR_FILENO, "\n", 1);
	exit(127);
}

void	print_error_open_file_and_exit(char *filename, char *error)
{
	ft_putstr_fd(filename, 2);
	perror(error);
	exit (EXIT_FAILURE);
}

void	print_error_msg_and_exit(char *error)
{
//	ft_putstr_fd("c", 2);
	perror(error);
	exit (EXIT_FAILURE);
}

void	print_error_msg_and_exit_positive(char *error)
{
	perror(error);
	exit (EXIT_SUCCESS);
}


//void	print_failed_cmd_msg_and_exit(char *error)
//{
//	perror(error);
//	exit (127);
//}
