#include "../minishell.h"

int	check_is_builtin(t_cline *node, t_data_shell *p, t_env *lst)
{
	if (!p || !node || !node->options || !node->options[0] || !lst)
		return (1);
	if (ft_strcmp(node->options[0], "cd") == 0)
	{
		if (!node->options[1])
			node->options[1] = NULL;
		return (ft_cd(p, lst, node->options[1]), 0);
	}
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
	if (ft_strcmp(node->options[0], "exit") == 0)
		return (ft_exit(node, p), 0);
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

int	print_envs(t_env *lst)
{
	while (lst)
	{
		if (lst->name)
		{
			printf("declare -x ");
			printf("%s",lst->name);
		}
		if (lst->value)
		{
			printf("=");
			printf("%s",lst->value);
		}
		printf("\n");
		lst = lst -> next;
	}
	return (0);
}

int	is_valid_identifier(int c)
{
	if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) || (c == '_'))
		return (0);
	return (1);
}