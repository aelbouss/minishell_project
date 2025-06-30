#include "../minishell.h"

int	ft_len(int nbr)
{
	int len;

	len = 0;
	len = (nbr <= 0 ? 1 : 0);
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}
char		*s_itoa(int n)
{
	unsigned int	nbr;
	int				sign;
	int				len;
	char			*alpha;

	sign = (n < 0 ? 1 : 0);
	alpha = NULL;
	len = ft_len(n);
	nbr = (n < 0 ? -n : n);
	if ((alpha = malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	alpha[len--] = '\0';
	while (len >= 0)
	{
		alpha[len] = nbr % 10 + '0';
		nbr /= 10;
		len--;
	}
	if (sign == 1)
		alpha[0] = '-';
	return (alpha);
}

void	__default_setup__(t_data_shell *mshell)
{
	mshell->line.head = NULL; 
	mshell->exit_status = 0;
	mshell->env_list = NULL;
	mshell->nc = 0;
	mshell->r_sign = 0;
}

void	shell_lvl_handling(t_data_shell *mshell)
{
	int nbr;
	char	*s_nbr;
	char	*gnbr;

	s_nbr = get_env_value(mshell->env_list, "SHLVL");
	if (s_nbr)
	{
		nbr = ft_atoi(s_nbr);
		nbr++;
		free(s_nbr);
		gnbr = s_itoa(nbr);
		if (gnbr)
		{
			modify_env_var(mshell->env_list, "SHLVL", gnbr);
			free(gnbr);
		}
	}
}