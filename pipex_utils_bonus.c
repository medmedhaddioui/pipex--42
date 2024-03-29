/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:20:46 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/21 20:33:33 by mel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	file_open(const char *filename, int i, t_data *o)
{
	int	fd;

	if (i == 0)
	{
		if (access(filename, F_OK))
			ft_exit("Error input file", o, FLAG2);
		fd = open(filename, O_RDONLY, 0644);
		if (fd == -1)
			ft_exit("Error input file", o, FLAG2);
		return (fd);
	}
	else if (i == 1)
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		close_pipes(o);
		ft_exit("Error output file", o, FLAG2);
	}
	return (fd);
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
			ft_exit(NULL, o, FLAG1);
	}
	if (cmd[0] == '.')
		return (NULL);
	if (!env)
		return (NULL);
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

void	close_pipes(t_data *o)
{
	int	i;

	i = 0;
	while (i < o->pipes)
	{
		close(o->arr[i][0]);
		close(o->arr[i][1]);
		free(o->arr[i]);
		i++;
	}
	free(o->arr);
}

int	**creat_pipes(t_data *o)
{
	int	i;
	int	**arr_pipes;

	i = 0;
	arr_pipes = malloc(o->pipes * sizeof(int *));
	if (!arr_pipes)
		return (NULL);
	while (i < o->pipes)
	{
		arr_pipes[i] = malloc(2 * sizeof(int));
		if (!arr_pipes[i])
		{
			while (i > 0)
			{
				free(arr_pipes[i]);
				i--;
			}
			free(arr_pipes);
			return (NULL);
		}
		if (pipe(arr_pipes[i]) < 0)
			ft_exit("error pipe", o, FLAG2);
		i++;
	}
	return (arr_pipes);
}
