#include "../minishell.h"

int	ft_pwd(t_minishell *p)
{
  char	*wdir;

  wdir = get_env_value(p, p->env_head, "PWD");
  if (!wdir)
		return (perror("pwd() failed"), 1);
	printf("%s\n",wdir);
  free(wdir);
  return (0);
}
