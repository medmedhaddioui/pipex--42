/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:20:01 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/07 14:10:03 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void parent(char **env ,char **av , data_b *o)
{
	o->i = 3;
	o->len = o->argc - 3;
	int x;
	x = 1;
	while (x < o->len)
	{
		o->pid2 = fork();
		if (o->pid2 == -1)
			ft_error("error fork_2");
		if (o->pid2 == 0)
		{
			if (x != o->argc - 4)
				child_middle(env, av, o);
			else if (x == o->argc - 4)
				child_last(env, av, o);
		}
		else
			x++;
	}
}
void	child_first(char **env, char **av, data_b *o)
{
	o->fdi = file_open(av[1], INFILE);
	o->cmd = ft_split(av[2], ' ');
	o->path = read_path(env, o->cmd[0]);
	if (dup2(o->fdi, STDIN) < 0)
		ft_error("Error dup2");          
	if (dup2(o->arr[o->j][1], STDOUT) < 0)
		ft_error("Error dup2 in child_first");
	close_pipes(o);
	if (execve(o->path, o->cmd, env) < 0)
		ft_error("Error in execve1");
}
void child_middle(char **env, char **av, data_b *o)
{
	o->cmd3 = ft_split(av[o->i++], ' ');
	o->path = read_path(env, o->cmd3[0]);
	if (dup2(o->arr[o->j][0],STDIN) < 0)
		perror("Error dup2");
	o->j++;
	if (dup2(o->arr[o->j][1], STDOUT) < 0)
		perror("Error dup2");
	close_pipes(o);
	if (execve(o->path, o->cmd3, env) < 0)
		ft_error("Error in execve3");
}
void	child_last(char **env, char **av, data_b *o)
{
	o->fdo = file_open(av[o-> argc - 1],OUTFILE);
	o->cmd2 = ft_split(av[o->i], ' ');
	o->path = read_path(env, o->cmd2[0]);
	if (dup2(o->arr[o->j][0], STDIN) < 0)
		ft_error("Error dup2 child_last");
	if (dup2(o->fdo, STDOUT) < 0)           
		ft_error("Error dup2 child_last");
	close_pipes(o);
	if (execve(o->path, o->cmd2, env) < 0)
		ft_error("Error in execve2");
}

int	main(int ac, char **av, char **env)
{
	data_b	o;

	if (ac < 3)
		return (0);
	o.argc = ac;
	o.pipes = ac - 4;
	o.arr = creat_pipes(&o);
	o.j = 0;
	o.pid = fork();
	if (o.pid == 0)
		child_first(env,av,&o);
	else
		parent(env,av,&o);
	// while (wait(NULL) > 0)
	// 	;
	return (0);
}
