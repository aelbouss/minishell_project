/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:53:21 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/10 16:37:16 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	loop_and_execute(t_cline *lst, char **envp, t_data_shell *p)
{
	int	fd_i;
	int	fd_o;

	if (!p || !lst)
		return (1);
	fd_i = dup(STDIN_FILENO);
	fd_o = dup(STDOUT_FILENO);
	p->fds[0] = fd_i;
	p->fds[1] = fd_o;
	count_her(p);
	p->nc = list_len(lst);
	if (p->nc > 1)
		many_commands(p, lst, envp);
	else
		one_cmd(p, lst, envp);
	if (p->r_sign != 0)
	{
		dup2(fd_i, STDIN_FILENO);
		dup2(fd_o, STDOUT_FILENO);
		p->r_sign = 0;
	}
	close(fd_i);
	close(fd_o);
	return (0);
}

void	clear_ressources(t_data_shell *p)
{
	free(p->line.rl);
	free_gc(&p->line.head);
	free_env_stuff(p->env_list);
	if (p->pwd)
		free(p->pwd);
}

int	many_commands(t_data_shell *p, t_cline *lst, char **envp)
{
	if (!p || !lst || !lst->options)
		return (1);
	if (heardoc_heandler(p, p->list) != 0)
		return (1);
	main_process(p, lst, envp);
	return (0);
}

void	secondary_env_list(t_data_shell *mshell)
{
	char	*tmp;
	char	*pwd;
	t_env	*node;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		return ;
	pwd = s_strjoin("PWD=", tmp);
	free(tmp);
	if (!pwd)
		return ;
	node = build_node(pwd);
	free(pwd);
	if (!node)
		return ;
	add_to_linkedlist(&mshell->env_list, node);
	create_minimal_envs(mshell);
}

void	puterr(char *keyword)
{
	printf("Minishell: warning here-docuentdelimited by `%s`\n", keyword);
}
