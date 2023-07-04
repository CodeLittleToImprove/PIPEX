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
		print_error_open_file_and_exit(filename, ERR_OPEN_FILE);
	return (ret);
}

int	has_file_access(const char *input_filename)
{
	int	input_access;
//	int	output_access;

	input_access = access(input_filename, R_OK);
//	output_access = access(output_filename, R_OK);
	if (input_access == 0)
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
	if (*env == NULL)
		return ("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:");
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
//		for (int i = 0; path_list[i] != NULL; i++)
//	{
//		ft_putstr_fd(path_list[i], 2);
//		ft_putstr_fd("\n", 2);
//	}
	s_cmd = ft_split(cmd, ' ');
	while (path_list[++i])
	{
		current_path = ft_strjoin(path_list[i], "/");
		exec_path = ft_strjoin(current_path, s_cmd[0]);
		free(current_path);
//		if (ft_strncmp(s_cmd[0], "", ft_strlen(s_cmd[0])) == 0)
//		{
//			print_error_msg_and_exit_positive(exec_path);
//		}
//		if (access(exec_path, F_OK) != 0)
//		{
//			print_error_msg_and_exit_positive(exec_path);
//		}
		if (access(exec_path, X_OK) == 0)
		{
			ft_free_array(s_cmd);
			return (exec_path);
		}
		free(exec_path);
	}
	ft_free_array(path_list);
	ft_free_array(s_cmd);
	print_error_cmd_not_found_and_exit(cmd, ERR_CMD);
	return (NULL);
}

char	**parse_command_with_quotes(char *cmd)
{
	int		c_index;
	char	quote_marker;
	char	**split_cmd;

	c_index = -1;

	while (cmd[++c_index])
	{
		if (cmd[c_index] == ' ')
			cmd[c_index] = '\x1A'; // ASCII character 26 represents the replaced space
		if (cmd[c_index] == '\'' || cmd[c_index] == '\"')
		{
			quote_marker = cmd[c_index];
			cmd[c_index] = '\x1A';
			while (cmd[c_index] != quote_marker && cmd[c_index])
				c_index++;
			cmd[c_index] = '\x1A';
		}
	}

	split_cmd = ft_split(cmd, 26);
	return (split_cmd);
}