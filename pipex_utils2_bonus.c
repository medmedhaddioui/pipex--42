/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:33:38 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/20 18:18:56 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_exit(t_data *o, int flag)
{
	if (flag == 0)
	{
		ft_free(o->cmd);
		write(2, "pipex: command not found:\n", 27);
		exit(EXIT_FAILURE);
	}
	else
	{
		write(2,"pipex: ",8);
		perror(o->cmd[0]);
		ft_free(o->cmd);
		exit(EXIT_FAILURE);
	}
}

void	ft_error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
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
	o->pid = fork();
	if (o->pid == 0)
	{
		if (dup2(o->arr[0][1], STDOUT) < 0)
			ft_error("Error dup2");
		o->s = get_next_line(0);
		while (o->s && ft_strcmp(o->s, av[2]) != 0)
		{
			ft_putstr_fd(o->s, 1);
			free(o->s);
			o->s = get_next_line(0);
		}
		free(o->s);
		close_pipes(o);
		exit(EXIT_SUCCESS);
	}
	parent(env, av, o);
	while (wait(NULL) > 0)
		;
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
