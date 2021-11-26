#include "builtins.h"

int	main(int argc, char *argv[])
{
	int		res;
	char	*home_path;

	res = 0;
	printf("pouet\n");
	if (argc == 1)
	{
		home_path = getenv("HOME");
		if (home_path)
			res = chdir(home_path);
	}
	else
		res = chdir(argv[1]);
	if (res == -1)
		perror(argv[1]);
}
