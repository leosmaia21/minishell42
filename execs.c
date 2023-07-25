#include "execs.h"

char *ft_findpath(t_envp *head, char **envp, char **flags)
{
    char *p;
    char **split;
    char *cmd_path;

    p = ft_find_value(head, "PATH");
    split = ft_split(p, ':');
    while (split)
	{
		cmd_path = ft_strjoin(*split++, "/");
        cmd_path = ft_strjoin(cmd_path, flags[0]);
		if (!cmd_path)
            break ;
		if (!access(cmd_path, F_OK))
			return(cmd_path);
		free(cmd_path);
		cmd_path = NULL;
	}
    perror(strerror(errno));
    return(NULL);
}


void	ft_single_exec(char **flags, char **envp, char *path)
{
	int		pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	    execve(path, flags, envp);
	waitpid(-1, &status, 0);
	ft_freedoublepointer(flags);
}