
#include "../../includes/minishell.h"

/**
 * pwd - Implements the behavior of the 'pwd' built-in command.
 *
 * This function prints the current working directory to the standard output. 
 * It uses the `getcwd()` function to retrieve the current directory and prints 
 * it. If `getcwd()` fails, the function returns an error code.
 *
 * @return int: Returns `NO_ERROR` if the current directory is printed 
 *              successfully, otherwise returns `ERROR` if `getcwd()` fails.
 */

int	pwd(void)
{
	char	cwd[1824];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ERROR);
	printf("%s\n", cwd);
	return (NO_ERROR);
}
