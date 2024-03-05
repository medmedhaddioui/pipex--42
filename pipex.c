/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:30:55 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/05 11:55:52 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



void parent(char **env ,char **av , data_t *o)
{
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
	if (dup2(o->fdi, STDIN) < 0)
		ft_error("Error dup2");
	if (dup2(o->fds[1], STDOUT) < 0)
		ft_error("Error dup2");
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
	if (dup2(o->fds[0], STDIN) < 0)
		ft_error("Error dup2");
	if (dup2(o->fdo, STDOUT) < 0)
		ft_error("Error dup2");
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
	waitpid(o.pid,NULL,0);
	return (0);
}
