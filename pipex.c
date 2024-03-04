/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:30:55 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/04 14:55:29 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	file_open(const char *filename, int i)
{
	int	fd;
	if (i == 1)
	{
		if (access(filename,F_OK))
			ft_error("Error infile");
		fd = open(filename, O_RDONLY, 0644);
		return fd;
	}
	else
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC , 0644);
	return (fd);
}
char	*read_path(char **env, char *av)
{
	char	**arr;
	int		i;

	i = 0;
	if (av[0] == '/')
		return (NULL);
	if (access(av, F_OK) != -1)
		return (av);
	while (ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	arr = ft_split(env[i], ':');
	i = 0;
	arr[i] = ft_strchr(arr[i], '/');
	av = ft_strjoin("/", av);
	arr[i] = ft_strjoin(arr[i], av);
	while (arr[i] != NULL && access(arr[i], F_OK) == -1)
	{
		i++;
		arr[i] = ft_strjoin(arr[i], av);
	}
	return (arr[i]);
}
void parent(char **env ,char **av , data_t *o)
{
		wait(NULL);
		o->pid2 = fork();
		if (o->pid2 == -1)
			ft_error("error fork_2");
		if (o->pid2 == 0)
			child_2(env, av, o);
}
void	child(char **env, char **av, data_t *o)
{
	close (o->fds[0]);
	o->fdi = file_open(av[1], INFILE);
	o->cmd = ft_split(av[2], ' ');
	o->path = read_path(env, o->cmd[0]);
	dup2(o->fdi, STDIN);
	dup2(o->fds[1], STDOUT);
	close(o->fds[1]);
	if (execve(o->path, o->cmd, env) < 0)
		ft_error("Error in execve1");
}

void	child_2(char **env, char **av, data_t *o)
{
	close (o->fds[1]);
	o->fdo = file_open(av[4],OUTFILE);
	o->cmd2 = ft_split(av[3], ' ');
	o->path = read_path(env, o->cmd2[0]);
	dup2(o->fds[0], STDIN);
	dup2(o->fdo, STDOUT);
	close(o->fds[0]);
	if (execve(o->path, o->cmd2, env) < 0)
		ft_error("Error in execve2");
}
int	main(int ac, char **av, char **env)
{
	data_t	o;

	if (ac != 5)
		return (0);
	if (pipe(o.fds) == -1)
		ft_error("Error pipe");
	o.pid = fork();
	if (o.pid == -1)
		ft_error("Error fork");
	if (o.pid == 0)	
		child(env, av, &o);
	else
		parent(env,av, &o);
	return (0);
}
