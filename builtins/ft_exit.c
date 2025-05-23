#include "../minishell.h"



//still needs work 
// if the  exit status isn't provided  ad  the first exit  with  the  exit sttus  of the last  process .
int	ft_exit(t_minishell *p)
{
	if (!p)
		return (perror("exit(failed)"), 1);
	if (!p->list->options[1])
		exit(0);
	else
		exit(ft_atoi(p->list->options[1]));
	return (0);
}