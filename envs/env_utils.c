#include "../minishell.h"

char	*extract_name(char *str)
{
	int	i;
	char	*name;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = s_substr(str, 0, i);
	if (!name)
		return (NULL);
	return (name);
}

char *extract_value(char *str)
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
			value = s_strdup(&str[i]);
			if (!value)
				return (NULL);
			return(value);
		}
		i++;
	}
	return (NULL);
}

int	split_each_env(char *str, char **name, char **value)
{
	if (!str)
		return (1);
	*name = extract_name(str);
	if (!name)
		return (1);
	*value = extract_value(str);
	if (!value)
		return (1);
	return (0);
}

t_env	*build_node(char *str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	if (split_each_env(str, &node->name, &node->value) != 0)
		return (NULL);
	node->flag = 0;
	node->next = NULL;
	return (node);
}

int	build_env_list(char *str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (1);
	if (split_each_env(str, &node->name, &node->value) != 0)
		return (1);
	node->flag = 0;
	node->next = NULL;
	return (0);
}
