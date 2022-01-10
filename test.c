#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
/*
	Redirect FD to STDIN
*/
int main()
{
	int fd = open("salut.txt", O_RDWR | O_APPEND);
	if (fork() == 0)
	{
		char **args;

		args = (char **) malloc(sizeof (char *) * 2);
		args[0] = strdup("cat");
		args[1] = NULL;
		dup2(fd, STDIN_FILENO);
		
		execve("/bin/cat", args, NULL);
		close(fd);
	}
	else
	{
		printf("Salut ceci est un test, fd=%d\n", fd);
		//dup2(fd, STDOUT_FILENO);
		//printf("Salut ceci est un test 2\n");
		close(fd);
	}
}