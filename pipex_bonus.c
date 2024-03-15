/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:20:01 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/15 00:37:06 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parent(char **env, char **av, t_data *o)
{
	o->len = o->argc - 3;
	o->x = 1;
	while (o->x < o->len)
	{
		o->pid2 = fork();
		if (o->pid2 == -1)
			ft_error("error fork_2");
		if (o->pid2 == 0)
		{
			if (o->x == o->len - 1)
				last_child(env, av, o);
			else
				n_child(env, av, o);
		}
		o->index_cmd++;
		o->x++;
		o->i++;
	}
	close_pipes(o);
	while (wait(NULL) > 0)
		;
}

void	first_child(char **env, char **av, t_data *o)
{
	o->fdi = file_open(av[1], INFILE);
	if (dup2(o->fdi, STDIN) < 0)
		ft_error("Error dup2");
	if (dup2(o->arr[o->i][1], STDOUT) < 0)
		ft_error("Error dup2 child_first");
	close_pipes(o);
	o->cmd = ft_split(av[2], ' ');
	if (!o->cmd[0])
		ft_exit();
	if (execve(read_path(env, o->cmd[0]), o->cmd, env) < 0)
	{
		ft_free(o->cmd);
		ft_error("Error in execve1");
	}
}

void	n_child(char **env, char **av, t_data *o)
{
	if (dup2(o->arr[o->i][0], STDIN) < 0)
		perror("Error dup2 middle");
	o->i++;
	if (dup2(o->arr[o->i][1], STDOUT) < 0)
		perror("Error dup2 middle");
	close_pipes(o);
	o->cmd = ft_split(av[o->index_cmd], ' ');
	if (!o->cmd[0])
		ft_exit();
	if (execve(read_path(env, o->cmd[0]), o->cmd, env) < 0)
	{
		ft_free(o->cmd);
		ft_error("Error in execve3");
	}
}

void	last_child(char **env, char **av, t_data *o)
{
	if (o->here_doc == 1)
		o->fdo = file_open(av[o->argc - 1], HERE_DOC_FILE);
	else
		o->fdo = file_open(av[o->argc - 1], OUTFILE);
	if (dup2(o->arr[o->i][0], STDIN) < 0)
		ft_error("Error dup2 child_last");
	if (dup2(o->fdo, STDOUT) < 0)
		ft_error("Error dup2 child_last");
	close_pipes(o);
	o->cmd = ft_split(av[o->index_cmd], ' ');
	if (!o->cmd[0])
		ft_exit();
	if (execve(read_path(env, o->cmd[0]), o->cmd, env) < 0)
	{
		ft_free(o->cmd);
		ft_error("Error in execve2");
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	o;

	if (ac < 3)
		return (0);
	o.argc = ac;
	o.pipes = ac - 4;
	o.arr = creat_pipes(&o);
	o.i = 0;
	o.index_cmd = 3;
	o.here_doc = 0;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		o.here_doc = 1;
		here_doc(env, av, &o);
		return (0);
	}
	o.pid = fork();
	if (o.pid == 0)
		first_child(env, av, &o);
	parent(env, av, &o);
	while (wait(NULL) > 0)
		;
	return (0);
}
