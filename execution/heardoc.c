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

/*
---> loop trough all the list
---> if you face here_doc executen it in  shild  process open  a  file  and  run it  inside .
---> and  du plicate stdin to  the  fd of  the  fd
---> and loop and do this whenever you  face heredoc 

*/

void generate_name(int *n, t_redr *file)
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

	fd = open(name,  O_CREAT | O_RDWR |  O_TRUNC , 0644);
	if (fd < 0)
		return (perror("error"), 1);
	return (fd);
}


void	heardoc_heandler(t_data_shell *p, t_cline *lst)
{
	t_redr	*sl;
	static int	idx;
	int			fd;
	pid_t		pid;

	if (!p || !lst)
		return	;
	while (lst)
	{
		sl = lst->r_list;
		while (sl)
		{
			if (ft_strcmp(sl->str, "<<") == 0)
			{
				generate_name(&idx, sl);
				fd = file_creation(sl->f_path);
				pid = heardoc(p, sl->file, fd);
				waitpid(pid, NULL, 0);
				close(fd);
			}
			sl = sl->next;
		}
		lst = lst->next;
	}
}

int	file_opener(char *name)
{
	int	fd;

	fd = open(name,  O_CREAT || O_RDWR || O_TRUNC);
	if (fd < 0)
		return (perror("error1"), 1);
	return (fd);
}


pid_t	heardoc(t_data_shell *mshell,  char *keyword, int fd)
{
	char	*line;
	pid_t	pid;

	(void) mshell;
	pid = fork();
	if (pid == -1)
		return(perror("fork"), 1);
	if (pid == 0)
	{
		while (1)
	 	{
	 		line = readline("heardoc> ");
		 	if (!line)
				return (perror("error"), 1);
			if (ft_strcmp(keyword, line) == 0)
				break;
			if( ft_strchr(line, '$') != NULL && (ft_strchr(keyword, '\'') != NULL || ft_strchr(keyword, '"') != NULL))
				line = her_fcts(mshell, line);
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		exit(0);
	}
	return (pid);
}
