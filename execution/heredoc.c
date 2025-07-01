/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:15:00 by aelbouss          #+#    #+#             */
/*   Updated: 2025/06/30 22:23:27 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_heredoc(t_cline *lst)
{
	t_redr	*s_lst;
	int		cnt;

	cnt = 0;
	while (lst)
	{
		s_lst = lst->r_list;
		while (s_lst)
		{
			if (ft_strcmp("<<", s_lst->str) == 0)
				cnt++;
			s_lst = s_lst ->next;
		}
		lst = lst -> next;
	}
	return (cnt);
}

void	generate_name(int *n, t_redr *file)
{
	file->f_path[0] = '/';
	file->f_path[1] = 't';
	file->f_path[2] = 'm';
	file->f_path[3] = 'p';
	file->f_path[4] = '/';
	file->f_path[5] = 'f';
	file->f_path[6] = *n + '0';
	file->f_path[7] = '\0';
	*n = *n + 1 ;
}

int	file_creation(char *name)
{
	int	fd;

	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("error"), 1);
	return (fd);
}

int	heardoc_heandler(t_data_shell *p, t_cline *lst)
{
	t_redr		*sl;
	static int	idx;

	if (!p || !lst)
		return (1);
	while (lst)
	{
		sl = lst->r_list;
		while (sl)
		{
			if (ft_strcmp(sl->str, "<<") == 0)
			{
				if (here_doc_routine(sl, p, idx) == 1)
					return (1);
			}
			sl = sl->next;
		}
		lst = lst->next;
	}
	return (0);
}

pid_t	heardoc(t_data_shell *mshell, char *keyword, int fd, int expand)
{
	char	*line;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		while (1)
		{
			signal(SIGINT, handler_2);
			signal(SIGQUIT, SIG_IGN);
			line = readline("heardoc> ");
			if (!line)
				return (puterr(keyword), 1);
			if (ft_strcmp(keyword, line) == 0)
				break ;
			if (ft_strchr(line, '$') != NULL && expand == 0)
				line = her_fcts(mshell, line);
			write_and_free(line, fd);
		}
		exit(0);
	}
	return (pid);
}
