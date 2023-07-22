#include "execs.h"

void ft_exec(t_envp *head, t_token *tokens, char **envp)
{
    char *p;
    char **split;
    char *cmd_path;
    char **flags;

    p = ft_find_value(head, "PATH");
    split = ft_split(p, ':');
    flags = jointokens(tokens);
    while (split)
	{
		cmd_path = ft_strjoin(*split++, "/");
        cmd_path = ft_strjoin(cmd_path, flags[0]);
        printf("%s\n", cmd_path);
		if (!cmd_path)
			perror(strerror(errno));
		if (!access(cmd_path, F_OK))
			break ;
		free(cmd_path);
		cmd_path = 0;
	}
    if (cmd_path)
    {
        if(execve(cmd_path, flags, envp) < 0)
            perror(strerror(errno));
    }
    else
        printf("Command not found");
}

