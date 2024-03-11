/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medmed <medmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:20:46 by mel-hadd          #+#    #+#             */
/*   Updated: 2024/03/11 20:06:22 by medmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex_bonus.h"

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
char	*read_path(char **env, char *cmd)
{
	char	**arr;
	int		i;
	char *path;

	i = 0;
	if (cmd[0] == '/')
		return (NULL);
	if (access(cmd, F_OK | X_OK) != -1)
		return (cmd);
	while (ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	arr = ft_split(ft_strchr(env[i],'/'), ':');
	path = find_path(arr, cmd);
	ft_free(arr);
	return path;
}

char *find_path (char **arr, char *cmd)
{
	int i;
	char *path;

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

void close_pipes(data_b *o)
{
	int i;
	i = 0;
	while (i < o->pipes)
	{
		close(o->arr[i][0]);
		close(o->arr[i][1]);
		i++;
	}
}

int  **creat_pipes(data_b *o)
{
	int i;
	i = 0;
	int **arr;
	arr = malloc (o->pipes * sizeof(int *));
	if (!arr)
		return NULL;
	while (i < o->pipes)
    {
        arr[i] = malloc(2 * sizeof(int));
        if (!arr[i])
        {
            while (i > 0)
            {
                free(arr[i]);
				i--;
			}
            free(arr);
            return NULL;
        }
		if (pipe(arr[i]) < 0)
			perror("Error pipe");
		i++;
    }
	return arr;
}