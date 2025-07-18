/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:59:52 by aelbouss          #+#    #+#             */
/*   Updated: 2025/07/10 17:33:39 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_is_dir(t_data_shell *p, char *path)
{
	struct stat	infos;

	if (stat(path, &infos) != 0)
		return (0);
	if (S_ISDIR(infos.st_mode))
	{
		printf("Minishell : %s : is a directory\n", path);
		p->exit_status = 126;
		return (1);
	}
	return (0);
}

void	wait_for_child(pid_t pid, t_data_shell *p)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		p->exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		p->exit_status = 128 + WTERMSIG(status);
		prompt_synchronisation(p->exit_status);
	}
}

int	check_permission(t_data_shell *p, char *path)
{
	if (access(path, W_OK | R_OK | X_OK) != 0)
	{
		perror("minishell: ");
		p->exit_status = 126;
		return (1);
	}
	return (0);
}

int	here_doc_routine(t_redr *sl, t_data_shell *p)
{
	pid_t	pid;
	int		fd;
	int		wait;

	wait = 0;
	generate_name(sl);
	fd = file_creation(sl->f_path);
	if (fd < 0)
		return (1);
	pid = heardoc(p, sl->file, fd, sl->h_expand);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &wait, 0);
	close(fd);
	if (WEXITSTATUS(wait) == 130)
	{
		p->exit_status = 130;
		return (1);
	}
	return (0);
}

void	write_and_free(char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	if (line)
		free(line);
}
