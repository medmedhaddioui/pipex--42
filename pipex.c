/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medmed <medmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:30:55 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/03 22:35:10 by medmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	file_open(const char *filename, int i)
{
	int	fd;
	if (i == 1)
	{
		if (access(filename,F_OK))
		{
			perror("error file");
			exit(0);
		}
		fd = open(filename, O_RDONLY, 0644);
		return fd;
	}
	else
		fd = open(filename, O_RDWR, 0644);
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
void	child(char **env, char **av, int fd_1)
{
	data_t	o;

	o.fdi = file_open(av[1], 1);
	o.cmd = ft_split(av[2], ' ');
	o.path = read_path(env, o.cmd[0]);
	dup2(o.fdi, 0);
	dup2(fd_1, 1);
	close(fd_1);
	if (execve(o.path, o.cmd, env) < 0)
		ft_error("error in execve1");
}

void	child_2(char **env, char **av, int fd_0)
{
	data_t	o;

	o.fdo = file_open(av[4],0);
	o.cmd2 = ft_split(av[3], ' ');
	o.path = read_path(env, o.cmd2[0]);
	dup2(fd_0, 0);
	dup2(o.fdo, 1);
	close(fd_0);
	if (execve(o.path, o.cmd2, env) < 0)
		ft_error("error in execve2");
}
int	main(int ac, char **av, char **env)
{
	data_t	o;

	if (ac == 1)
		return (0);
	if (pipe(o.fds) == -1)
		ft_error("error pipe");
	o.pid = fork();
	if (o.pid == -1)
		ft_error("error pipe");
	if (o.pid == 0)
	{
		close(o.fds[0]);
		child(env, av, o.fds[1]);
	}
	else
	{
		o.pid2 = fork();
		if (o.pid2 == 0)
		{
			close(o.fds[1]);
			child_2(env, av, o.fds[0]);
		}
	}
	return (0);
}
