/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:30:55 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/17 03:26:46 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	file_open(const char *filename, int i)
{
	int	fd;

	if (i == 1)
	{
		if (access(filename, F_OK))
			ft_error("Error infile");
		fd = open(filename, O_RDONLY, 0644);
		if (fd == -1)
			exit(EXIT_FAILURE);
		return (fd);
	}
	else
	{
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit(EXIT_FAILURE);
		return (fd);
	}
}

void	parent(char **env, char **av, t_data *o)
{
	o->pid2 = fork();
	if (o->pid2 == -1)
		ft_error("error fork_2");
	if (o->pid2 == 0)
		child_2(env, av, o);
	close(o->fds[1]);
	close(o->fds[0]);
	wait(NULL);
}

void	child(char **env, char **av, t_data *o)
{
	close(o->fds[0]);
	o->fdi = file_open(av[1], INFILE);
	if (dup2(o->fdi, STDIN) < 0 || dup2(o->fds[1], STDOUT) < 0)
		ft_error("Error dup2");
	o->cmd = ft_split(av[2], ' ');
	close(o->fds[1]);
	if (!o->cmd[0])
		ft_exit(o);
	o->path = read_path(env, o->cmd[0]);
	if (!o->path)
	{
		free(o->path);
		ft_exit(o);
	}
	if (execve(o->path, o->cmd, env) < 0)
		ft_error("Error in execve1");
}

void	child_2(char **env, char **av, t_data *o)
{
	close(o->fds[1]);
	o->fdo = file_open(av[4], OUTFILE);
	if (dup2(o->fds[0], STDIN) < 0 || (dup2(o->fdo, STDOUT) < 0))
		ft_error("Error dup2");
	close(o->fds[0]);
	o->cmd = ft_split(av[3], ' ');
	if (!o->cmd[0])
		ft_exit(o);
	o->path = read_path(env, o->cmd[0]);
	if (!o->path)
	{
		free(o->path);
		ft_exit(o);
	}
	if (execve(o->path, o->cmd, env) < 0)
		ft_error("Error in execve2");
}

int	main(int ac, char **av, char **env)
{
	t_data	o;

	if (ac != 5)
		exit(1);
	if (pipe(o.fds) == -1)
		ft_error("Error pipe");
	o.pid = fork();
	if (o.pid == -1)
		ft_error("Error fork");
	if (o.pid == 0)
		child(env, av, &o);
	parent(env, av, &o);
	wait(NULL);
	return (0);
}
