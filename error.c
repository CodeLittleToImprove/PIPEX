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
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(split_cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(127);
}

void	print_error_open_file_and_exit(char *filename, char *error)
{
	ft_putstr_fd(filename, STDERR_FILENO);
	perror(error);
	exit (EXIT_FAILURE);
}

void	print_error_msg_and_exit(char *error)
{
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
