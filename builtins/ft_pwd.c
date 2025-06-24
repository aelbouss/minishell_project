#include "../minishell.h"

int	ft_pwd(t_data_shell *p)
{
  char	*wdir;
  char  *swdir;

  swdir = NULL;
  wdir = get_env_value(p, p->env_list, "PWD");
  if (!wdir)
  {
    swdir = getcwd(NULL, 0);
	  printf("%s\n",swdir);
  }
  else
    printf("%s\n",wdir);
  if (swdir)
    free(swdir);
  return (0);
}
