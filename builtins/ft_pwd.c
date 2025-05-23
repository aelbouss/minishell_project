#include "../minishell.h"

int	ft_pwd(t_minishell *p)
{
  char	*wdir;

  wdir = get_env_value(p, p->env_head, "PWD");
  if (!wdir)
    wdir = getcwd(NULL, 0);
	printf("%s\n",wdir);
  free(wdir);
  return (0);
}