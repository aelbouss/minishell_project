#include "../minishell.h"

char	*extract_name(t_data_shell *p, char *str)
{
	int	i;
	char	*name;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = s_substr(p , str, 0, i);
	if (!name)
		return (NULL);
	return (name);
}

char *extract_value(t_data_shell *p, char *str)
{
	int	i;
	char	*value;

	if(!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1])
		{
			i++;
			value = s_strdup(p, &str[i]);
			if (!value)
				return (NULL);
			return(value);
		}
		i++;
	}
	return (NULL);
}

int	split_each_env(t_data_shell *p,	char *str, char **name, char **value)
{
	if (!p ||!str)
		return (1);
	*name = extract_name(p, str);
	if (!name)
		return (1);
	*value = extract_value(p, str);
	if (!value)
		return(1);
	return (0);
}

t_env	*build_node(t_data_shell *p,  char *str)
{
	t_env	*node;

	node = fg_malloc(sizeof(t_env), &p->fgc);
	if (!node)
		return (NULL);
	if (split_each_env(p, str, &node->name, &node->value)!= 0)
		return (NULL);
	node->flag = 0;
	node->next = NULL;
	return (node);
}

int	build_env_list(t_data_shell *p, char *str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (1);
	if (split_each_env(p, str, &node->name, &node->value)!= 0)
		return (1);
	node->flag = 0;
	node->next = NULL;
	return (0);
}
 
