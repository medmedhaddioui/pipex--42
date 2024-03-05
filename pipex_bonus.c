/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:20:01 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/05 18:01:10 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void parent(char **env ,char **av , data_b *o)
{
	int pipe_fd[o->len][2];
	while (o->i < o->len)
	{
		if (pipe(pipe_fd[o->i]) < 0)
			perror("Error pipe");
		o->i++;
	}
	o->i = 0;
	// while (o->len < o->i)
	// {
	// 	o->pid = fork();
	// 	if (o->pid == 0)
	// 		child_n();
	// 	else
	// 		child_wr
	// }
		// o->pid2 = fork();
		// if (o->pid2 == -1)
		// 	ft_error("error fork_2");
		// if (o->pid2 == 0)
		// 	child_2(env, av, o);
}
// void close_files(int **pipe_fd)
// {
// 	close(pipe_fd)
// }
void	child_first(char **env, char **av, data_b *o, int **pipe_fd)
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
// void child_n(char *env, char *av, data_b *o)
// {
	
// }
void	child_last(char **env, char **av, data_b *o)
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
	data_b	o;

	if (ac < 3)
		return (0);	
	o.len = ac - 4;
	o.i = 0;
	if (pipe(o.fds) == -1)
		ft_error("Error pipe");
	o.pid = fork();
	if (o.pid < 0)
		perror("Error fork");
	if (o.pid == 0)
		child(env, av, &o);
	parent(env,av, &o);
	return (0);
}
