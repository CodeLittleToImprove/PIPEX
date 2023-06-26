# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

int	has_file_access(const char *input_filename, const char *output_filename)
{
	int	input_access;
	int	output_access;

	input_access = access(input_filename, R_OK);
	output_access = access(output_filename, R_OK);
	printf("%d\n %d\n", input_access, output_access);
	if (input_access == 0 && output_access == 0)
		return (0);
	else
		return (-1);
}

int	main(int argc, char *argv[] )
{
	int ret = has_file_access(argv[1], argv[4]);
	printf("%d", ret);
	return 0;
}
