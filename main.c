# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

char **parse_command_with_quotes(char *cmd)
{
	int c_index = -1;
	char buf;
	char **split;

	while (cmd[++c_index])
	{
		if (cmd[c_index] == ' ')
			cmd[c_index] = '\x1A'; // ASCII character 26 represents the replaced space
		if (cmd[c_index] == '\'' || cmd[c_index] == '\"')
		{
			buf = cmd[c_index];
			cmd[c_index] = '\x1A';
			while (cmd[c_index] != buf && cmd[c_index])
				c_index++;
			cmd[c_index] = '\x1A';
		}
	}

	// Placeholder return value
	return NULL;
}

int main(void)
{
	char input[] = "ls -l \"my files\" /path/to/directory";

	// Use the parsed output as needed

	return 0;
}

