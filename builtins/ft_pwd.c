#include "../minishell.h"

int	ft_pwd(t_data_shell *p)
{
  char	*wdir;

  wdir = get_env_value(p, p->env_list, "PWD");
  if (!wdir)
    wdir = getcwd(NULL, 0);
	printf("%s\n",wdir);
  return (0);
}
