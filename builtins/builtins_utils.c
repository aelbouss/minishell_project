#include "../minishell.h"

int	check_is_builtin(t_cline *node, t_data_shell *p, t_env *lst)
{
	if (!p || !node || !node->options || !node->options[0]|| !lst)
		return (1);
	if (ft_strcmp(node->options[0], "cd") == 0)
		return (ft_cd(p, lst, node->options[1]), 0);
	if (ft_strcmp(node->options[0], "env") == 0)
		return (ft_env(p), 0);
	if (ft_strcmp(node->options[0], "export") == 0)
		return (ft_export(p, node), 0);
	if (ft_strcmp(node->options[0], "echo") == 0)
		return(ft_echo(node->options), 0);
	if (ft_strcmp(node->options[0], "pwd") == 0)
		return (ft_pwd(p), 0);
	if (ft_strcmp(node->options[0], "unset") == 0)
		return (ft_unset(p, &p->env_list), 0);
	return (1);
}

int	search_for_char(char *s, int n)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == n)
			return (1);
		i++;
	}
	return (0);
}
