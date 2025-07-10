/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:15:00 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/10 17:49:21 by aelbouss         ###   ########.fr       */
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
			s_lst = s_lst->next;
		}
		lst = lst->next;
	}
	return (cnt);
}

void	generate_name(t_redr *file)
{
	int	fd;
	int	rb;

	file->f_path[0] = '/';
	file->f_path[1] = 't';
	file->f_path[2] = 'm';
	file->f_path[3] = 'p';
	file->f_path[4] = '/';
	file->f_path[5] = 'f';
	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
	{
		perror("error");
		exit(1);
	}
	rb = read(fd, file->f_path + 6, 4);
	if (rb <= 0)
	{
		perror("error");
		exit(1);
	}
	file->f_path[10] = '\0';
	close(fd);
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
	t_redr	*sl;

	if (!p || !lst)
		return (1);
	while (lst)
	{
		sl = lst->r_list;
		while (sl)
		{
			if (ft_strcmp(sl->str, "<<") == 0)
			{
				if (here_doc_routine(sl, p) == 1)
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
			signals_heredoc();
			line = readline("heardoc> ");
			if (!line)
				perr_exit(keyword, mshell, fd);
			if (ft_strcmp(keyword, line) == 0)
				break ;
			if (ft_strchr(line, '$') != NULL && expand == 0)
				her_fcts(fd, mshell, line);
			else
				write_and_free(line, fd);
			line = NULL;
		}
		close_fds_exit(mshell, fd);
	}
	return (pid);
}
