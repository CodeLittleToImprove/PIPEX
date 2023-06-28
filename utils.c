/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:10:39 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/06/13 18:10:39 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	open_input_or_output_file(char *filename, char *in_or_out)
{
	int	ret;

	ret = 0;

	if (ft_strncmp(in_or_out, "input", ft_strlen(in_or_out)) == 0)
		ret = open(filename, O_RDONLY, 0666);
	else if (ft_strncmp(in_or_out, "output", ft_strlen(in_or_out)) == 0)
		ret = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		print_error_msg_and_exit(ERR_IMPOSSIBLE);
	if (ret == -1)
		print_error_msg_and_exit(ERR_OPEN_FAIL);
	return (ret);
}

int	has_file_access(const char *input_filename, const char *output_filename)
{
	int	input_access;
	int	output_access;

	input_access = access(input_filename, R_OK);
	output_access = access(output_filename, R_OK);
	if (input_access == 0 && output_access == 0)
		return (1);
	else
		return (0);
}


char	*get_env_value_by_name(char *envVarName, char **env)
{
	int		i;
	char	*equal_sign_pos;
	char	*path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], envVarName, ft_strlen(envVarName)) == 0)
		{
			equal_sign_pos = ft_strchr(env[i], '=');
			if (equal_sign_pos)
			{
				path = equal_sign_pos + 1;
				return (path);
			}
		}
		i++;
	}
	return (NULL);
}

char	*get_exec_path(char *cmd, char **env)
{
	int		i;
	char	*exec_path;
	char	**path_list;
	char	*current_path;
	char	**s_cmd;

	i = -1;
	path_list = ft_split(get_env_value_by_name("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (path_list[++i])
	{
		current_path = ft_strjoin(path_list[i], "/");
		exec_path = ft_strjoin(current_path, s_cmd[0]);
		free(current_path);
		if (access(exec_path, X_OK) == 0)
		{
			ft_free_array(s_cmd);
			return (exec_path);
		}
		free(exec_path);
	}
	ft_free_array(path_list);
	ft_free_array(s_cmd);
	print_error_cmd_not_found_and_exit(cmd);
	return (NULL);
}

