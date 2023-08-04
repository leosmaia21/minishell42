#ifndef ENVP_H
# define ENVP_H

typedef struct s_envp{
	char			*var;
	char			*key;
	struct s_envp	*next;
}	t_envp;

#endif
