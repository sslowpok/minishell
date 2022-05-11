#include "../includes/minishell.h"

int	main(__unused int argc, char **argv, char **envp)
{
	char	*a = "ls -l";
	char **flags = ft_split(a, ' ');

	// execve(block->argv[0], block->argv, envp);
	if (!access("/bin/ls", F_OK))
		printf("access done\n");

	printf("%s\n%s\n%s\n", flags[0], flags[1], flags[2]);
	if (execve("/bin/ls", flags, envp) < 0)
		printf("error\n");
}