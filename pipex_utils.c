/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hadd <mel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:08:09 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/09 15:29:37 by mel-hadd         ###   ########.fr       */
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
		return (fd);
	}
	else
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

char	*read_path(char **env, char *arg)
{
	char	**arr;
	int		i;
	char *path;
	char *cmd;

	i = 0;
	if (arg[0] == '/')
		return (NULL);
	if (access(arg, F_OK | X_OK) != -1)
		return (arg);
	while (ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	arr = ft_split(env[i], ':');
	i = 0;
	arr[i] = ft_strchr(arr[i], '/');
	cmd = ft_strjoin("/", arg);
	path = ft_strjoin(arr[i], cmd);
	while (path != NULL && access(path, F_OK | X_OK) == -1)
	{		
		i++;
		free(path);
		path = ft_strjoin(arr[i], cmd);
	}
	free(cmd);
	ft_free(arr);
	return (path);
}
void ft_free(char **arr)
{
	int i;
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
