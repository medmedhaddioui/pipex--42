/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:33:38 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/21 21:00:26 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_exit(char *s, t_data *o, int flag)
{
	if (flag == 0)
	{
		ft_free(o->cmd);
		write(2, "pipex: command not found:\n", 27);
		exit(EXIT_FAILURE);
	}
	if (flag == 1)
	{
		write(2, "pipex: ", 8);
		perror(o->cmd[0]);
		ft_free(o->cmd);
		exit(EXIT_FAILURE);
	}
	else
		perror(s);
	exit(EXIT_FAILURE);
}

int	ft_wait(t_data *o)
{
	int	status;

	waitpid(o->pid_last, &status, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (s1[i] == '\n' && s2[i] == '\0')
		return (0);
	return (s1[i] - s2[i]);
}

void	here_doc(char **env, char **av, t_data *o)
{
	o->arr = creat_pipes(o);
	write(1, "here_doc <> ", 13);
	o->s = get_next_line(0);
	while (o->s && ft_strcmp(o->s, av[2]) != 0)
	{
		write(1, "here_doc <> ", 13);
		ft_putstr_fd(o->s, o->arr[0][1]);
		free(o->s);
		o->s = get_next_line(0);
	}
	get_next_line(-1);
	free(o->s);
	parent(env, av, o);
}

void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
