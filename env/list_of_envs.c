#include "../minishell.h"

char	*extract_value(char *s, t_minishell *p)
{
	char	*value;
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
		{
			i++;
			value = ft_strdup(&s[i]);
			add_to_list(&p->line.head, ft_gc_new(value));
			if (!value)
				return (NULL);
			return (value);
		}
		i++;
	}
	return (NULL);
}

char	*extract_name(char *s, t_minishell *p)
{
	int	i;
	char	*name;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	name = ft_substr(s, 0, i);
	add_to_list(&p->line.head, ft_gc_new(name));
	if (!name)
		return (NULL);
	return (name);
}

int	split_each_env(char *s, char **name, char **value, t_minishell *p)
{
	*value = extract_value(s,p);
	if (!*value)
	{
		printf("hnaya 1");
		return(1);
	}
	*name = extract_name(s,p);
	if (!*name)
		return(1);
	return (0);
}

t_env	*build_node(t_minishell *p, char *str)
{
	t_env	*node;

	node = gc_malloc(sizeof(t_env), &(p->line.head));
	if (!node)
		return (NULL);
	if (split_each_env(str, &node->name, &node->value, p)!= 0)
		return (NULL);
	node->flag = 0;
	node->next = NULL;
	return (node);
}

void	add_to_linkedlist(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !*lst)
		*lst = new ;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	create_env_list(t_minishell *p, char **envp)
{
	t_env	*newnode;
	int		i;

	p->env_head = NULL ;
	i = 0;
	while (envp[i])
	{
		newnode = build_node(p, envp[i]);
		if (!newnode)
		{
			printf("Bad Allocation\n");
			return ;
		}
		add_to_linkedlist(&(p->env_head), newnode);
		i++;
	}
}