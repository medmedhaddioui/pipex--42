/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:08:09 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/21 00:16:16 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*read_path(char **env, char *cmd, t_data *o)
{
	char	**arr;
	int		i;
	char	*path;

	i = 0;
	if (access(cmd, F_OK | X_OK) != -1)
		return (cmd);
	while (cmd[i])
	{
		if (cmd[i++] == '/')
			ft_exit(o, FLAG1);
	}
	if (cmd[0] == '.')
			return NULL;
	if (!env)
		return NULL;
	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	arr = ft_split(ft_strchr(env[i], '/'), ':');
	path = find_path(arr, cmd);
	ft_free(arr);
	return (path);
}

char	*find_path(char **arr, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	cmd = ft_strjoin("/", cmd);
	path = ft_strjoin(arr[i], cmd);
	while (path != NULL && access(path, F_OK | X_OK) == -1)
	{
		free(path);
		i++;
		path = ft_strjoin(arr[i], cmd);
	}
	free(cmd);
	return (path);
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

void	ft_error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}
